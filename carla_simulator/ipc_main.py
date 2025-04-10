# IPC_main.py
from multiprocessing import Process, Manager
from grpc_server import serve
from carla_data_collector import start_data_collection

if __name__ == "__main__":
    print("🚀 Launching CARLA Data Collector + gRPC Server...")
    with Manager() as manager:
        shared_data = manager.dict()

        carla_process = Process(target=start_data_collection, args=(shared_data,))
        grpc_process = Process(target=serve, args=(shared_data,))

        carla_process.start()
        grpc_process.start()

        print("🟢 Both processes started. Press Ctrl+C to stop.")

        try:
            carla_process.join()
            grpc_process.join()
        except KeyboardInterrupt:
            print("\n🛑 KeyboardInterrupt detected. Terminating...")
            carla_process.terminate()
            grpc_process.terminate()
            carla_process.join()
            grpc_process.join()
            print("✅ All processes terminated.")
