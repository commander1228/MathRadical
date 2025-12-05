from math_engine_client import math_engine, MathEngineException
import grpc
import sys


def main():
    """
    Initializes the MathEngineClient and tests the GCD calculation service.
    """
    print("--- Starting Simple gRPC GCD Test ---")

    # Instantiate the client
    client = None
    try:
        client = math_engine()
        # Explicitly wait for the channel to be ready
        client._wait_for_channel_ready()

    except (ConnectionError, Exception) as e:
        print(f"\nFATAL ERROR: Could not initialize client or connect to server: {e}")
        print("Please ensure your C++ MathEngineServer is running on localhost:50051.")
        sys.exit(1)

    # Define test inputs
    num1 = 60
    num2 = 48

    print(f"\nAttempting to calculate GCD({num1}, {num2})...")

    try:
        # Call the core method on the client
        result = client.calculate_gcd(num1, num2)

        # Check the expected result (GCD of 60 and 48 is 12)
        expected = 12
        if result == expected:
            print(f"✅ SUCCESS! The server returned {result}. Expected {expected}.")
        else:
            print(f"⚠️ TEST FAILED. Server returned {result}, but expected {expected}.")

    except MathEngineException as e:
        print(f"❌ Application Error: The C++ server rejected the input. Details: {e}")
    except grpc.RpcError as e:
        print(f"❌ Transport Error: gRPC communication failed. Details: {e.details()}")
    except Exception as e:
        print(f"❌ Unexpected Python Error: {e}")

    print("\n--- Test Finished ---")


if __name__ == '__main__':
    main()