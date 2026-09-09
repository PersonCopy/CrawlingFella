# This script is for testing commands via UDP to the robot.
import socket
import json
import time

UDP_IP = '192.168.0.226'
UDP_PORT = 5005

angle = 0

while True:
    obj = {
        "A0" : angle, # 450, 2800 accurate from 0-90, then map 90-165 to 90-180
        "A1" : angle,
        "A2" : 90
        }

    payload = json.dumps(obj)

    angle += 45
    angle = 0 if angle > 180 else angle
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(payload.encode('utf-8'), (UDP_IP, UDP_PORT))
    time.sleep(2)