import grpc
import sys
import os
import time

# --- Setup for importing generated files ---
# This assumes the 'gen' folder is present and contains the compiled Protobuf files.
sys.path.append(os.path.join(os.path.dirname(__file__), 'gen'))
# Import generated Protobuf message types and the client stub
try:
    from MathEngine_pb2 import TwoWholeNumbers, WholeNumberResultReply
    from MathEngine_pb2_grpc import MathEngineStub
except ImportError as e:
    print(f"FATAL: Could not import generated gRPC files. Have you run 'protoc' into the 'gen' folder? Error: {e}")
    sys.exit(1)


# Define a custom exception for clean error reporting
class MathEngineException(Exception):
    """Custom exception for application-level errors returned by the C++ server."""
    pass


class math_engine:

    def __init__(self, server_address='localhost:50051'):
        """Initializes the gRPC channel and client stub."""
        print(f"Initializing Math Engine client, connecting to {server_address}...")
        self.server_address = server_address
        self.channel = grpc.insecure_channel(server_address)
        self.stub = MathEngineStub(self.channel)

    def _wait_for_channel_ready(self, timeout=3):
        """Ensures the channel is ready before making calls."""
        try:
            # Blocks until the channel is ready or timeout expires
            grpc.channel_ready_future(self.channel).result(timeout=timeout)
            print("Connection established successfully.")
        except grpc.FutureTimeoutError:
            # This happens if the C++ server is not running
            raise ConnectionError(f"Connection to gRPC server at {self.server_address} timed out.")

    def calculate_gcd(self, num1: int, num2: int) -> int:
        request = TwoWholeNumbers(number1=num1, number2=num2)

        try:
            response: WholeNumberResultReply = self.stub.GreatestCommonDenominator(request)

            if response.success:
                if response.result_values:
                    return response.result_values[0]
                else:
                    raise MathEngineException("Server returned success but no result value.")
            else:
                raise MathEngineException(response.error_message)

        except grpc.RpcError as e:
            print(f"\n❌ gRPC Transport Error Details:")
            print(f"  Status Code: {e.code()}")
            print(f"  Details: {e.details()}")
            raise


def run_tests():
    """Main function to test the MathEngineClient with various scenarios."""

    # Instantiate the client
    client = math_engine()

    try:
        # Check for connection before running tests
        client._wait_for_channel_ready()
    except ConnectionError as e:
        print(f"FATAL: {e}. Please ensure the C++ server is running and accessible.")
        return
    except Exception as e:
        print(f"An unexpected error occurred during connection: {e}")
        return

    print("\n" + "=" * 50)
    print("TEST SUITE STARTED")
    print("=" * 50)

    # --- Test Case 1: Valid Inputs (Expected Success) ---
    print("\n[TEST 1] Testing GCD(48, 18) - Expected: Success, Result: 6")
    try:
        result = client.calculate_gcd(48, 18)
        print(f"✅ Success. GCD(48, 18) = {result}")
    except (MathEngineException, grpc.RpcError) as e:
        print(f"❌ Failure. Unexpected error: {e}")

    # --- Test Case 2: Validation Failure (Expected Application Error) ---
    print("\n[TEST 2] Testing GCD(0, 0) - Expected: Validation Error")
    try:
        result = client.calculate_gcd(0, 0)
        print(f"❌ Failure. Unexpected success: Result was {result}")
    except MathEngineException as e:
        print(f"✅ Success. Caught expected validation error: {e}")
    except grpc.RpcError:
        print("❌ Failure. Unexpected transport error.")

    print("\n" + "=" * 50)
    print("TEST SUITE FINISHED")
    print("=" * 50)


if __name__ == '__main__':
    run_tests()