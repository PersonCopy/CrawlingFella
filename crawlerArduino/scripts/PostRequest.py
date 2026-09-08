# This script is for testing commands via POST to the robot.
import requests

url = 'http://192.168.0.226'
obj = {}

x = requests.post(url, json = obj)

print(x.text)