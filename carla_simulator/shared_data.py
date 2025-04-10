# shared_data.py
from multiprocessing import Manager

manager = Manager()
shared_data = manager.dict()

# Initialize default values
shared_data['speed'] = 0.0
shared_data['distance'] = 0.0
shared_data['lane_offset'] = 0.0
shared_data['steering_angle'] = 0.0
shared_data['traffic_sign'] = ""
shared_data['brake_status'] = False
shared_data['acceleration'] = 0.0
