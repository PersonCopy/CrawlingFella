# This script is for testing commands via POST to the robot.
import requests

url = 'http://192.168.0.226/servo'
obj = {
    "A0" : 0,
    "A1" : 0,
    "A2" : 0
    }

x = requests.post(url, json = obj)

print(x.text)