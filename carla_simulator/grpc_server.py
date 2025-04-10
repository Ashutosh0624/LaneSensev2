import grpc
from concurrent import futures
import time

import carla_pb2
import carla_pb2_grpc
from shared_data import shared_data

# gRPC server class based on CarlaDataService
class CarlaDataServiceServicer(carla_pb2_grpc.CarlaDataServiceServicer):
    def GetSensorData(self, request, context):
        # Prepare the response message using shared data
        response = carla_pb2.SensorResponse(
            speed=shared_data.get("speed", 0.0),
            acceleration=shared_data.get("acceleration", 0.0),
            steering=shared_data.get("steering", 0.0),
            brake=shared_data.get("brake", 0.0),
            throttle=shared_data.get("throttle", 0.0),
            lane_offset=shared_data.get("lane_offset", 0.0),
            traffic_sign=shared_data.get("traffic_sign", "None"),
            status=shared_data.get("status", "unknown")
        )
        print(f"[gRPC] Request ID: {request.request_id} → Responding with sensor data")
        return response

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    carla_pb2_grpc.add_CarlaDataServiceServicer_to_server(CarlaDataServiceServicer(), server)
    server.add_insecure_port('[::]:50051')
    print("[gRPC] Server started on port 50051...")
    server.start()

    try:
        while True:
            time.sleep(86400)  # Keep server alive
    except KeyboardInterrupt:
        print("[gRPC] Server stopping...")
        server.stop(0)

if __name__ == "__main__":
    serve()
