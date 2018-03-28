import serial
import csv

import serial
ser = serial.Serial('/dev/ttyACM0')
ser.flushInput()

while True:
    try:
        ser_data = ser.readline()
        decoded_data = float(ser_data[0:len(ser_data)-2].decode("utf-8"))
        print(decoded_bytes)
    except:
        print("Keyboard Interrupt")
        break
    
       # f = open('output.csv', 'a')	
       # while True:
       # Read a line and convert it from b'xxx\r\n' to xxx
       # line = ser.readline().decode('utf-8')]
       # if line:  # If it isn't a blank line
       # f.write(line)
       # f.close()
