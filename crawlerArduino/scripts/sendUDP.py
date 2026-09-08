# This script is for testing commands via UDP to the robot.
import socket
import json

UDP_IP = '192.168.0.226'
UDP_PORT = 5005

obj = {
    "A0" : 90,
    "R1" : 45,
    "A2" : 90
    }

payload = json.dumps(obj)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(payload.encode('utf-8'), (UDP_IP, UDP_PORT))