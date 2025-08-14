import serial
import time

class ThrusterController:
    def __init__(self, port='/dev/ttyACM0', baudrate=9600):
        try:
            self.arduino = serial.Serial(port, baudrate, timeout=1)
            time.sleep(2)
            print(f"Conectado al Arduino en {port}")
        except serial.SerialException as e:
            print(f"Error conectando al Arduino: {e}")
            self.arduino = None
    
    def send_command(self, command):
        if self.arduino:
            self.arduino.write((command + '\n').encode())
            time.sleep(0.1)
            while self.arduino.in_waiting:
                response = self.arduino.readline().decode().strip()
                if response:
                    print(f"Arduino: {response}")
    
    def move_motors(self, motor_pwm_pairs, duration):

        cmd_parts = []
        for motor, pwm in motor_pwm_pairs:
            cmd_parts.append(f"{motor} {pwm}")
        cmd_parts.append(str(duration))
        command = ' '.join(cmd_parts)
        print(f"Enviando: {command}")
        self.send_command(command)
    
    def close(self):
        if self.arduino:
            self.arduino.close()
            print("Conexión cerrada")

def main():
    controller = ThrusterController()
    if not controller.arduino:
        return
    
    try:
        while True:
            user_input = input("Ingresa motores y PWM (ej: '1 1600 2 1400 5') o 'quit': ").strip()
            if user_input.lower() == 'quit':
                break
            parts = user_input.split()
            if len(parts) < 3 or len(parts) % 2 == 0:
                print("Formato incorrecto. Debe ser: motor1 pwm1 motor2 pwm2 ... duracion")
                continue
            try:
                duration = int(parts[-1])
                motor_pwm_pairs = []
                for i in range(0, len(parts)-1, 2):
                    motor = int(parts[i])
                    pwm = int(parts[i+1])
                    motor_pwm_pairs.append((motor, pwm))
                controller.move_motors(motor_pwm_pairs, duration)
            except ValueError:
                print("Todos los valores deben ser números enteros")
                
    except KeyboardInterrupt:
        print("\nInterrumpido por el usuario")
    finally:
        controller.close()

if __name__ == "__main__":
    main()
