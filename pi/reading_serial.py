import serial

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
