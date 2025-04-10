# carla_data_collector.py
import carla
import time
import random
from shared_data import shared_data

def spawn_vehicle(world, blueprint_library):
    bp = blueprint_library.filter('vehicle.*')[0]
    spawn_point = random.choice(world.get_map().get_spawn_points())
    vehicle = world.spawn_actor(bp, spawn_point)
    vehicle.set_autopilot(True)
    print("[INFO] Vehicle spawned and autopilot enabled.")
    return vehicle

def get_speed(vehicle):
    velocity = vehicle.get_velocity()
    return 3.6 * (velocity.x**2 + velocity.y**2 + velocity.z**2)**0.5  # km/h

def start_data_collection():
    client = carla.Client("localhost", 2000)
    client.set_timeout(5.0)
    world = client.get_world()

    blueprint_library = world.get_blueprint_library()
    vehicle = spawn_vehicle(world, blueprint_library)

    shared_data["status"] = "running"

    try:
        while True:
            shared_data["speed"] = round(get_speed(vehicle), 2)
            shared_data["acceleration"] = vehicle.get_acceleration().x
            shared_data["steering"] = vehicle.get_control().steer
            shared_data["brake"] = vehicle.get_control().brake
            shared_data["throttle"] = vehicle.get_control().throttle
            shared_data["lane_offset"] = vehicle.get_transform().location.y  # simplified
            # TODO: Add traffic sign detection logic

            print("[CARLA] Speed:", shared_data["speed"], "km/h")
            time.sleep(0.1)

    except KeyboardInterrupt:
        print("[INFO] Shutting down...")
    finally:
        vehicle.destroy()
        shared_data["status"] = "stopped"
        print("[INFO] Vehicle destroyed.")

if __name__ == "__main__":
    start_data_collection()
