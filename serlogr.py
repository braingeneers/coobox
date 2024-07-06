# Noah Williams

"""
PROGRAM DESCRIPTION:
    Read and log data from serial port, created for visualizing PID results.
    TODO: Produce CSV file with data, filename as mmddyy_hhmmss.csv for reference.

GOALS:
    1. Read in data from serial port
    2. Log data to file
    3. Plot data 

NOTES:
    ls /dev/tty.*  to view all serial ports

"""

# Libraries
import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import csv
import time

# Constants
FILENAME = time.strftime("%m%d%y_%H%M%S") + '.csv'
SERIAL_PORT = '/dev/tty.usbmodem1101'
BAUD_RATE = 9600
TIMEOUT = 1

# Variables
timePoints = []
tmp102Data = []
pwmData = []


# Open serial port
def openPort():
    try :
        open_port = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=TIMEOUT) 
        print("Serial port is open")
        return open_port
    except serial.SerialException:
        print("Serial port is not open -- Exiting program")
        exit()
    

openPort = openPort()

def readData(debug=True):
    data = openPort.readline().decode('utf-8').strip().split(',')
    if len(data) == 3:
        pwmData.append(float(data[0]))
        tmp102Data.append(float(data[1]))
        timePoints.append(float(data[2]))

        if debug: print(data[0], data[1], data[2])


def update_plot(frame):
    readData()
    plt.cla() # Clear the plot
    plt.plot(timePoints, tmp102Data)

    # Plot PWM data
    # plt.plot(timePoints, pwmData)

    # Plot line at 28 degrees
    plt.plot([timePoints[0], timePoints[-1]], [30, 30], 'r--')

    plt.ylim(26, 32)
    plt.xlabel('Time (s)')
    plt.ylabel('Temperature (C)')
    plt.title('Temperature vs Time')



fig, axs = plt.subplots()
animation = FuncAnimation(fig, update_plot, interval=50)
plt.show()