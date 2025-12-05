from flask import Flask, jsonify
from flask_cors import CORS
from math_engine_client import math_engine, MathEngineException
import grpc
import os

app = Flask(__name__)
CORS(app)

# Initialize gRPC client
# We might want to do this lazily or on startup.
# For now, let's try to initialize it globally, but handle connection errors gracefully.
try:
    # Use environment variable for server address if available, else default
    server_address = os.environ.get('MATH_ENGINE_SERVER', 'localhost:50051')
    client = math_engine(server_address=server_address)
except Exception as e:
    print(f"Warning: Could not initialize gRPC client: {e}")
    client = None

@app.route('/gcd/<int:a>/<int:b>', methods=['GET'])
def get_gcd(a, b):
    if not client:
        return jsonify({'error': 'Backend service unavailable'}), 503
    
    try:
        result = client.calculate_gcd(a, b)
        return jsonify({'result': result, 'success': True})
    except MathEngineException as e:
        return jsonify({'error': str(e), 'success': False}), 400
    except grpc.RpcError as e:
        return jsonify({'error': f"RPC Error: {e.details()}", 'success': False}), 500
    except Exception as e:
        return jsonify({'error': str(e), 'success': False}), 500

@app.route('/lcm/<int:a>/<int:b>', methods=['GET'])
def get_lcm(a, b):
    # Stub for LCM as backend doesn't support it yet
    return jsonify({'error': 'Not Implemented', 'success': False}), 501

@app.route('/health', methods=['GET'])
def health():
    return jsonify({'status': 'ok'}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
