cmake_minimum_required(VERSION 3.16)

project(ADAS_inustrial_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6
find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

# Add the executable
qt_add_executable(appADAS_inustrial_app
    main.cpp
    main.qml
    configparser.h
    configparser.cpp
    logger.h
    logger.cpp
    safetyLogging.h
    errormanager.h
    errormanager.cpp
    sensordatamodel.h
    sensordatamodel.cpp
    carla.pb.h
    carla.pb.cc
    carla.grpc.pb.h
    carla.grpc.pb.cc
    qt_grpc_client.h
    qt_grpc_client.cpp
)

# Add QML module
qt_add_qml_module(appADAS_inustrial_app
    URI ADAS_inustrial_app
    VERSION 1.0
    QML_FILES main.qml
)

# Set target properties
set_target_properties(appADAS_inustrial_app PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Compile definitions
target_compile_definitions(appADAS_inustrial_app
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

# Manually specify include and link directories for gRPC and Protobuf
include_directories(/usr/include)
link_directories(/usr/lib/x86_64-linux-gnu)

target_link_libraries(appADAS_inustrial_app
    PRIVATE
        Qt6::Quick
        grpc++
        grpc
        protobuf
)
