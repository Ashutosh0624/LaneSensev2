# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import carla_pb2 as carla__pb2


class CarlaDataServiceStub(object):
    """Missing associated documentation comment in .proto file."""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.GetSensorData = channel.unary_unary(
                '/carla.CarlaDataService/GetSensorData',
                request_serializer=carla__pb2.SensorRequest.SerializeToString,
                response_deserializer=carla__pb2.SensorResponse.FromString,
                )


class CarlaDataServiceServicer(object):
    """Missing associated documentation comment in .proto file."""

    def GetSensorData(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_CarlaDataServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'GetSensorData': grpc.unary_unary_rpc_method_handler(
                    servicer.GetSensorData,
                    request_deserializer=carla__pb2.SensorRequest.FromString,
                    response_serializer=carla__pb2.SensorResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'carla.CarlaDataService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


 # This class is part of an EXPERIMENTAL API.
class CarlaDataService(object):
    """Missing associated documentation comment in .proto file."""

    @staticmethod
    def GetSensorData(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/carla.CarlaDataService/GetSensorData',
            carla__pb2.SensorRequest.SerializeToString,
            carla__pb2.SensorResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
