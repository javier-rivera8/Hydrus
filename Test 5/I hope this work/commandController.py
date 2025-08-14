import serial
import time

PORT = "/dev/ttyACM0"
BAUD = 9600

# Connect to Arduino
ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)  # Wait for Arduino reset

print("Connected to Arduino.")
print("Commands: F=Forward, B=Back, L=Left, R=Right, U=Up, D=Down, S=Stop, Q=Quit")

while True:
    cmd = input("Enter command: ").strip().upper()

    if cmd == "Q":
        print("Exiting...")
        break

    if cmd in ["F", "B", "L", "R", "U", "D", "S"]:
        ser.write(cmd.encode())
        print(f"Sent: {cmd}")
    else:
        print("Invalid command!")

ser.close()

