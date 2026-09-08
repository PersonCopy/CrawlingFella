# This script is for testing commands via POST to the robot.
import requests

url = 'http://192.168.0.226/servo'
obj = {
    "A0" : 20,
    "A1" : 250,
    "A2" : 50
    }

x = requests.post(url, json = obj)

print(x.text)