# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: carla.proto
# Protobuf Python Version: 4.25.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0b\x63\x61rla.proto\x12\x05\x63\x61rla\"#\n\rSensorRequest\x12\x12\n\nrequest_id\x18\x01 \x01(\t\"\xa3\x01\n\x0eSensorResponse\x12\r\n\x05speed\x18\x01 \x01(\x01\x12\x14\n\x0c\x61\x63\x63\x65leration\x18\x02 \x01(\x01\x12\x10\n\x08steering\x18\x03 \x01(\x01\x12\r\n\x05\x62rake\x18\x04 \x01(\x01\x12\x10\n\x08throttle\x18\x05 \x01(\x01\x12\x13\n\x0blane_offset\x18\x06 \x01(\x01\x12\x14\n\x0ctraffic_sign\x18\x07 \x01(\t\x12\x0e\n\x06status\x18\x08 \x01(\t2P\n\x10\x43\x61rlaDataService\x12<\n\rGetSensorData\x12\x14.carla.SensorRequest\x1a\x15.carla.SensorResponseb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'carla_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_SENSORREQUEST']._serialized_start=22
  _globals['_SENSORREQUEST']._serialized_end=57
  _globals['_SENSORRESPONSE']._serialized_start=60
  _globals['_SENSORRESPONSE']._serialized_end=223
  _globals['_CARLADATASERVICE']._serialized_start=225
  _globals['_CARLADATASERVICE']._serialized_end=305
# @@protoc_insertion_point(module_scope)
