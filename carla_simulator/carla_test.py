import carla
import time

def main():
    # Carla se connection setup
    client = carla.Client("localhost", 2000)
    client.set_timeout(10.0)

    world = client.get_world()
    blueprint_library = world.get_blueprint_library()

    # Vehicle spawn karte hain
    bp = blueprint_library.filter('vehicle.tesla.model3')[0]
    spawn_point = world.get_map().get_spawn_points()[0]
    vehicle = world.spawn_actor(bp, spawn_point)
    print("Vehicle spawned!")

    # Camera sensor attach karte hain
    camera_bp = blueprint_library.find('sensor.camera.rgb')
    camera_transform = carla.Transform(carla.Location(x=1.5, z=2.4))
    camera = world.spawn_actor(camera_bp, camera_transform, attach_to=vehicle)

    def process_image(image):
        print(f"[Camera Frame] Frame: {image.frame}, Size: {image.width}x{image.height}")

    camera.listen(lambda image: process_image(image))

    print("Camera listening...")

    # Test duration
    time.sleep(10)

    # Cleanup
    camera.stop()
    camera.destroy()
    vehicle.destroy()
    print("Test finished. Sensors and vehicle destroyed.")

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("Interrupted by user.")
