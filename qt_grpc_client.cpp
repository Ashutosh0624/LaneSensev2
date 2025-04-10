#include "qt_grpc_client.h"

QtGrpcClient::QtGrpcClient(const std::string& server_address) {
    auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    stub_ = carla::CarlaDataService::NewStub(channel);
}

SensorData QtGrpcClient::getSensorData() {
    SensorData data;
    carla::EmptyRequest request;
    carla::SensorData response;
    grpc::ClientContext context;

    grpc::Status status = stub_->GetSensorData(&context, request, &response);

    if (status.ok()) {
        data.speed = response.speed();
        data.acceleration = response.acceleration();
        data.steering = response.steering();
        data.brake = response.brake();
        data.throttle = response.throttle();
        data.lane_offset = response.lane_offset();
        data.traffic_sign = response.traffic_sign();
        data.status = response.status();
    } else {
        data.status = "Error: " + status.error_message();
    }

    return data;
}
