#include "Math/Fraction.h"
#include "Math/MathUtils.h"
#include "MathEngine.grpc.pb.h" // Generated gRPC header
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "MathEngineValidator.h"

// --- Standard gRPC Imports ---
using grpc::ServerContext;
using grpc::Status;

//messages
using RadMath::TwoWholeNumbers;
using RadMath::WholeNumberResultReply;


// Assuming your math class/functions are in a namespace (e.g., math_core)
// using math_core::FactorizationSolver;
// using math_core::GraphingEngine;

// 1. The Service Implementation Class
class MathEngineServiceImpl final : public RadMath::MathEngine::Service {

public:

  Status GreatestCommonDenominator(ServerContext* context,
        const TwoWholeNumbers* request,
        WholeNumberResultReply* response
    ) override {
    RadMath::MathEngineValidator Validator;
    long long num1 = request->number1();
    long long num2 = request->number2();
    std::vector<long long> numbers = {num1,num2};
    Validator.ValidateNotAllZeros(numbers);
    if (!Validator.wasValid()) {
      Validator.printErrors();
    }
      int64_t result = RadMath::MathUtils::GCD(num1,num2,false);
      response -> add_result_values(result);
      response ->set_success(true);

    return grpc::Status::OK;
  }

};
  // 2. Server Startup Boilerplate
  void RunServer() {
    std::string server_address("0.0.0.0:50051");
    MathEngineServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "C++ Math Engine Server listening on " << server_address << std::endl;

    server->Wait();
  }

int main() {
  RunServer();
  return 0;
}