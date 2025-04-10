# carla_data_collector.py
import carla
import time
import random

def spawn_vehicle(world, blueprint_library):
    bp = blueprint_library.filter('vehicle.*')[0]
    spawn_point = random.choice(world.get_map().get_spawn_points())
    vehicle = world.spawn_actor(bp, spawn_point)
    vehicle.set_autopilot(True)
    print("[CARLA] ✅ Vehicle spawned and autopilot enabled.")
    return vehicle

def get_speed(vehicle):
    velocity = vehicle.get_velocity()
    return 3.6 * (velocity.x**2 + velocity.y**2 + velocity.z**2)**0.5  # km/h

def start_data_collection(shared_data):
    print("[CARLA] 🧠 Shared dict ID:", id(shared_data))
    client = carla.Client("localhost", 2000)
    client.set_timeout(5.0)
    world = client.get_world()

    blueprint_library = world.get_blueprint_library()
    vehicle = spawn_vehicle(world, blueprint_library)

    shared_data["status"] = "running"
    shared_data["sensor_ok"] = True

    try:
        while True:
            if vehicle.is_alive:
                shared_data["speed"] = round(get_speed(vehicle), 2)
                shared_data["acceleration"] = vehicle.get_acceleration().x
                shared_data["steering"] = vehicle.get_control().steer
                shared_data["brake"] = vehicle.get_control().brake
                shared_data["throttle"] = vehicle.get_control().throttle
                shared_data["lane_offset"] = vehicle.get_transform().location.y
                shared_data["traffic_sign"] = "None"
                shared_data["sensor_ok"] = True
                shared_data["status"] = "running"
                print(f"[CARLA] Speed: {shared_data['speed']} km/h")
            else:
                print("[CARLA] ❌ Vehicle destroyed.")
                shared_data["sensor_ok"] = False
                shared_data["status"] = "stopped"
                break
            time.sleep(0.1)

    except KeyboardInterrupt:
        print("[CARLA] ❗ Keyboard Interrupt detected.")
    finally:
        try:
            vehicle.destroy()
            print("[CARLA] 🧹 Vehicle destroyed.")
        except:
            pass
        shared_data["status"] = "stopped"
        shared_data["sensor_ok"] = False
