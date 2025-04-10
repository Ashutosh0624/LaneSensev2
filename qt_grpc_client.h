#ifndef QT_GRPC_CLIENT_H
#define QT_GRPC_CLIENT_H

#include <string>
#include "carla.grpc.pb.h"
#include "carla.pb.h"
#include <grpcpp/grpcpp.h>

struct SensorData {
    float speed = 0.0f;
    float acceleration = 0.0f;
    float steering = 0.0f;
    float brake = 0.0f;
    float throttle = 0.0f;
    float lane_offset = 0.0f;
    std::string traffic_sign = "None";
    std::string status = "Unknown";
};

class QtGrpcClient {
public:
    QtGrpcClient(const std::string& server_address = "localhost:50051");
    SensorData getSensorData();

private:
    std::unique_ptr<carla::CarlaDataService::Stub> stub_;
};

#endif // QT_GRPC_CLIENT_H
