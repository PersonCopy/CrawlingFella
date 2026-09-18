# This script is for testing commands via POST to the robot.
import requests

'''
=== THIS IS LEGACY CODE ===
'''

url = 'http://192.168.0.226/servo'
obj = {
    "A0" : 90,
    "A1" : 90,
    "A2" : 90
    }

x = requests.post(url, json = obj)

print(x.text)