use axum::{
    extract::{Path, State},
    routing::get,
    Json, Router,
    http::StatusCode,
    response::IntoResponse,
};
use serde_json::{json, Value};
use std::env;
use std::net::SocketAddr;
use tower_http::cors::CorsLayer;

pub mod rad_math {
    // tonic/prost generates snake_case filenames for packages. 
    // RadMath -> rad_math.rs or radmath.rs? 
    // Based on previous error, RadMath.rs didn't exist.
    // Let's try matching the module structure generated.
    tonic::include_proto!("rad_math"); 
}

use rad_math::math_engine_client::MathEngineClient;
use rad_math::TwoWholeNumbers;
use tonic::transport::Channel;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 1. Configure Backend Connection
    let backend_url = env::var("MATH_ENGINE_SERVER").unwrap_or_else(|_| "http://[::1]:50051".to_string());
    // Ensure URL has scheme
    let backend_url = if !backend_url.starts_with("http") {
        format!("http://{}", backend_url)
    } else {
        backend_url
    };

    println!("Connecting to backend at: {}", backend_url);

    // 2. Initialize gRPC Client
    // We try to connect lazily or eagerly. For resilience, we'll connect per request or hold a channel.
    // Tonic channels are cheap to clone and thread-safe.
    let channel = Channel::from_shared(backend_url)?
        .connect_lazy();
    
    let client = MathEngineClient::new(channel);

    // 3. Define Router
    let app = Router::new()
        .route("/health", get(health_check))
        .route("/gcd/:a/:b", get(get_gcd))
        .route("/lcm/:a/:b", get(get_lcm))
        .layer(CorsLayer::permissive())
        .with_state(client);

    // 4. Start Server
    let port = env::var("PORT").unwrap_or_else(|_| "5000".to_string());
    let addr: SocketAddr = format!("0.0.0.0:{}", port).parse()?;
    
    println!("Rust Gateway listening on {}", addr);
    
    let listener = tokio::net::TcpListener::bind(addr).await?;
    axum::serve(listener, app).await?;

    Ok(())
}

async fn health_check() -> Json<Value> {
    Json(json!({ "status": "ok", "gateway": "rust" }))
}

async fn get_gcd(
    Path((a, b)): Path<(i64, i64)>,
    State(mut client): State<MathEngineClient<Channel>>,
) -> impl IntoResponse {
    let request = tonic::Request::new(TwoWholeNumbers {
        number1: a,
        number2: b,
    });

    match client.greatest_common_denominator(request).await {
        Ok(response) => {
            let inner = response.into_inner();
            (StatusCode::OK, Json(json!({
                "success": inner.success,
                "result": inner.result_values.first(),
                "all_results": inner.result_values
            })))
        }
        Err(status) => (StatusCode::INTERNAL_SERVER_ERROR, Json(json!({
            "success": false,
            "error": format!("gRPC Error: {}", status.message())
        }))),
    }
}

async fn get_lcm(
    Path((a, b)): Path<(i64, i64)>,
    State(mut client): State<MathEngineClient<Channel>>,
) -> impl IntoResponse {
    // The C++ Server doesn't expose LCM, but it does expose GCD.
    // We replicate the C++ MathUtils::LCM logic here: (a / gcd) * b
    
    let request = tonic::Request::new(TwoWholeNumbers {
        number1: a,
        number2: b,
    });

    match client.greatest_common_denominator(request).await {
        Ok(response) => {
            let inner = response.into_inner();
            
            if !inner.success || inner.result_values.is_empty() {
                 return (StatusCode::INTERNAL_SERVER_ERROR, Json(json!({
                    "success": false,
                    "error": format!("Backend failed to calculate GCD: {}", inner.error_message)
                })));
            }

            let gcd = inner.result_values[0];
            
            if gcd == 0 {
                return (StatusCode::OK, Json(json!({
                    "success": true,
                    "result": 0,
                    "all_results": vec![0]
                })));
            }

            let result = (a / gcd) * b;

            (StatusCode::OK, Json(json!({
                "success": inner.success,
                "result": result,
                "all_results": vec![result]
            })))
        }
        Err(status) => (StatusCode::INTERNAL_SERVER_ERROR, Json(json!({
            "success": false,
            "error": format!("gRPC Error: {}", status.message())
        }))),
    }
}
