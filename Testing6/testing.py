import serial
import sys
import re
import time

class ThrusterController:
    def __init__(self, port='/dev/ttyACM0', baudrate=9600):
        try:
            self.arduino = serial.Serial(port, baudrate, timeout=1)
            time.sleep(2)  # Wait for Arduino to initialize
            print(f"Connected to Arduino on {port}")
        except serial.SerialException as e:
            print(f"Error connecting to Arduino: {e}")
            sys.exit(1)
    
    def parse_command(self, command):
        """Parse command like 'front(motor 7 1600 motor 8 1600, 20s)', 'delay(5s)', or predefined movements"""
        # Extract command name and parameters
        command_match = re.match(r'(\w+)\((.*)\)', command)
        if not command_match:
            print(f"Invalid command format: {command}")
            return None
        
        command_name = command_match.group(1).lower()
        parameters = command_match.group(2)
        
        # Handle delay command
        if command_name == 'delay':
            # Extract delay duration
            time_match = re.search(r'(\d+)s?', parameters)
            if time_match:
                duration = int(time_match.group(1))
                return command_name, [], duration  # No motor commands for delay
            else:
                print("Invalid delay format. Use: delay(10s)")
                return None
        
        # Check if there's a time parameter for motor commands
        duration = 0
        time_match = re.search(r',\s*(\d+)s', parameters)
        if time_match:
            duration = int(time_match.group(1))
            # Remove time parameter from parameters string
            parameters = re.sub(r',\s*\d+s', '', parameters)
        
        # Extract motor commands
        motor_commands = []
        motor_matches = re.findall(r'motor\s+(\d+)\s+(\d+)', parameters)
        
        for motor_num, speed in motor_matches:
            motor_commands.append((int(motor_num), int(speed)))
        
        return command_name, motor_commands, duration
    
    def send_to_arduino(self, motor_commands):
        """Send motor commands to Arduino"""
        for motor_num, speed in motor_commands:
            command = f"{motor_num},{speed}\n"
            self.arduino.write(command.encode())
            print(f"Sent: Motor {motor_num} -> {speed}")
            time.sleep(0.1)  # Small delay between commands
    
    def stop_motors(self, motor_commands):
        """Stop specified motors by setting them to neutral (1500)"""
        for motor_num, _ in motor_commands:
            command = f"{motor_num},1500\n"
            self.arduino.write(command.encode())
            print(f"Stopped: Motor {motor_num} -> 1500")
            time.sleep(0.1)
    
    def execute_commands(self, commands):
        """Execute list of commands"""
        for command in commands:
            parsed = self.parse_command(command)
            if parsed:
                command_name, motor_commands, duration = parsed
                
                # Handle delay command
                if command_name == 'delay':
                    print(f"Waiting for {duration} seconds...")
                    time.sleep(duration)
                    print("Delay completed")
                else:
                    # Handle motor commands
                    print(f"Executing {command_name}:")
                    
                    # Send motor commands
                    self.send_to_arduino(motor_commands)
                    
                    # If duration is specified, wait and then stop motors
                    if duration > 0:
                        print(f"Running for {duration} seconds...")
                        time.sleep(duration)
                        print("Stopping motors...")
                        self.stop_motors(motor_commands)
                
                time.sleep(0.5)  # Delay between command groups
    
    def close(self):
        if hasattr(self, 'arduino'):
            self.arduino.close()

def main():
    if len(sys.argv) < 2:
        print("Usage examples:")
        print("  python3 testing.py 'delay(20s)' 'front(motor 7 1600 motor 8 1600, 15s)'")
        print("  python3 testing.py 'front(motor 7 1600 motor 8 1600, 20s)'")
        print("  python3 testing.py 'back(motor 7 1400 motor 8 1400, 10s)'")
        print("  python3 testing.py 'up(motor 4 1600 motor 6 1600, 5s)'")
        print("  python3 testing.py 'down(motor 4 1400 motor 6 1400, 3s)'")
        print("  python3 testing.py 'left(motor 1 1600 motor 3 1400, 2s)'")
        print("  python3 testing.py 'right(motor 1 1400 motor 3 1600, 2s)'")
        print("\nAvailable commands: delay, front, back, up, down, left, right")
        print("Time parameter is optional for motor commands. Without time, motors will stay at set speed.")
        print("Delay command format: delay(10s) - waits for specified seconds")
        sys.exit(1)
    
    controller = ThrusterController()
    
    try:
        # Get commands from command line arguments
        commands = sys.argv[1:]
        controller.execute_commands(commands)
    except KeyboardInterrupt:
        print("\nStopping...")
        # Emergency stop all motors
        for i in range(1, 9):
            controller.arduino.write(f"{i},1500\n".encode())
    finally:
        controller.close()

if __name__ == "__main__":
    main()