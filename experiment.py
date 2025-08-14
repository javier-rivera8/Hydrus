import serial
import time

class ThrusterController:
    def __init__(self, port='/dev/ttyACM0', baudrate=9600):
        try:
            self.arduino = serial.Serial(port, baudrate, timeout=1)
            time.sleep(2)  # Esperar a que se establezca la conexión
            print(f"Conectado al Arduino en {port}")
        except serial.SerialException as e:
            print(f"Error conectando al Arduino: {e}")
            self.arduino = None
    
    def send_command(self, command):
        if self.arduino:
            self.arduino.write((command + '\n').encode())
            time.sleep(0.1)
            
            # Leer respuesta del Arduino
            if self.arduino.in_waiting:
                response = self.arduino.readline().decode().strip()
                print(f"Arduino: {response}")
    
    def forward(self, duration):
        command = f"forward {duration}"
        print(f"Enviando: {command}")
        self.send_command(command)
    
    def stop(self):
        print("Enviando: stop")
        self.send_command("stop")
    
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
            user_input = input("Ingresa comando (ej: 'forward 5', 'stop', 'quit'): ").strip()
            
            if user_input.lower() == 'quit':
                break
            elif user_input.lower() == 'stop':
                controller.stop()
            elif user_input.startswith('forward'):
                try:
                    parts = user_input.split()
                    if len(parts) == 2:
                        duration = int(parts[1])
                        controller.forward(duration)
                    else:
                        print("Formato: forward [segundos]")
                except ValueError:
                    print("Duración debe ser un número entero")
            else:
                print("Comando no reconocido. Usa 'forward [segundos]', 'stop' o 'quit'")
                
    except KeyboardInterrupt:
        print("\nInterrumpido por el usuario")
    finally:
        controller.close()

if __name__ == "__main__":
    main()