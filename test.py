import serial
import time

# Configuration
SERIAL_PORT = "/dev/ttyACM0"  # Same as in your upload.sh
BAUD_RATE = 115200
NUM_THRUSTERS = 8

# PWM values (matching your Arduino code limits)
PWM_NEUTRAL = 1500
PWM_FORWARD = 1600  # Forward thrust

def connect_arduino():
    """Connect to Arduino via serial"""
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=2)
        time.sleep(2)  # Wait for Arduino to initialize
        print(f"Connected to Arduino on {SERIAL_PORT}")
        return ser
    except serial.SerialException as e:
        print(f"Error connecting to Arduino: {e}")
        return None

def send_command(ser, thruster_num, pwm_value):
    """Send command to specific thruster"""
    command = f"T{thruster_num}:{pwm_value}\n"
    ser.write(command.encode())
    
    # Read response
    response = ser.readline().decode().strip()
    print(f"Sent: {command.strip()} -> Response: {response}")
    return response

def test_all_thrusters(ser):
    """Turn on each thruster for 3 seconds, turn off, then move to next"""
    print("\n=== Starting All Thrusters Sequential Test ===")
    
    for thruster in range(1, NUM_THRUSTERS + 1):
        print(f"\n--- Testing Thruster {thruster} ---")
        
        # Turn ON thruster
        print(f"Turning ON T{thruster} (PWM: {PWM_FORWARD})")
        send_command(ser, thruster, PWM_FORWARD)
        time.sleep(3)  # Run for 3 seconds
        
        # Turn OFF thruster
        print(f"Turning OFF T{thruster} (PWM: {PWM_NEUTRAL})")
        send_command(ser, thruster, PWM_NEUTRAL)
        time.sleep(1)  # Brief pause before next thruster
        
        print(f"T{thruster} test complete")
    
    print("\n=== All Thrusters Test Complete ===")

def emergency_stop_all(ser):
    """Set all thrusters to neutral"""
    print("\n=== Emergency Stop - Setting all thrusters to neutral ===")
    for thruster in range(1, NUM_THRUSTERS + 1):
        send_command(ser, thruster, PWM_NEUTRAL)
        time.sleep(0.1)

def main():
    # Connect to Arduino
    ser = connect_arduino()
    if not ser:
        return
    
    try:
        # Wait for Arduino ready message
        print("Waiting for Arduino to be ready...")
        for _ in range(5):
            line = ser.readline().decode().strip()
            if line:
                print(f"Arduino: {line}")
        
        # Run the test sequence for all thrusters
        test_all_thrusters(ser)
        
    except KeyboardInterrupt:
        print("\n\nTest interrupted by user")
        emergency_stop_all(ser)
        
    except Exception as e:
        print(f"\nError during test: {e}")
        emergency_stop_all(ser)
        
    finally:
        if ser:
            emergency_stop_all(ser)
            ser.close()
            print("Serial connection closed")

if __name__ == "__main__":
    main()