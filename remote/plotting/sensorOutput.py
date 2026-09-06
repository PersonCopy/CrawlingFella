import serial
import numpy as np
import matplotlib.pyplot as plt
import ast

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

# Live updating plot.
plt.ion()
fig, ax = plt.subplots()

ax.set_xlim(-200, 200)
ax.set_ylim(-200, 200)
ax.grid(True)
ax.set_aspect('equal', adjustable='box')

# Initial vector of size 0 at origin.
q = ax.quiver(0, 0, 0, 0, color='b', units='xy', scale=1)

while True:
    x,y,click = ast.literal_eval(ser.readline().decode().strip())
    print(x, y, click)

    # Draw vector.
    q.set_UVC(x, y)

    if click == 1:
        q.set_color("r")
    else:
        q.set_color("b")

    plt.pause(0.01)


ser.close()