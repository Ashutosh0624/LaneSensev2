# grpc_server.py
import grpc
from concurrent import futures
import time

import carla_pb2
import carla_pb2_grpc

def serve(shared_data):
    print("[gRPC] 🚀 Server starting... Shared dict ID:", id(shared_data))
    class CarlaDataServiceServicer(carla_pb2_grpc.CarlaDataServiceServicer):
        def GetSensorData(self, request, context):
            response = carla_pb2.SensorResponse(
                speed=shared_data.get("speed", 0.0),
                acceleration=shared_data.get("acceleration", 0.0),
                steering=shared_data.get("steering", 0.0),
                brake=shared_data.get("brake", 0.0),
                throttle=shared_data.get("throttle", 0.0),
                lane_offset=shared_data.get("lane_offset", 0.0),
                traffic_sign=shared_data.get("traffic_sign", "None"),
                status=shared_data.get("status", "unknown"),
                sensor_ok=shared_data.get("sensor_ok", False)
            )
            print(f"[gRPC] ✅ Request received → SensorOK: {response.sensor_ok} | Speed: {response.speed}")
            return response

    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    carla_pb2_grpc.add_CarlaDataServiceServicer_to_server(CarlaDataServiceServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("[gRPC] ✅ Server started on port 50051...")

    try:
        while True:
            time.sleep(86400)
    except KeyboardInterrupt:
        print("[gRPC] ❌ Server shutting down...")
        server.stop(0)
