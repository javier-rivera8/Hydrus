import serial
import time
import argparse
import sys

# Configuración del puerto serie (ajusta según tu Arduino)
ARDUINO_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

# Inicializar conexión serie
try:
    arduino = serial.Serial(ARDUINO_PORT, BAUD_RATE)
    time.sleep(2)  # Espera que Arduino se inicialice
    print(f"Conectado a Arduino en {ARDUINO_PORT}")
except Exception as e:
    print(f"No se pudo conectar a Arduino: {e}")
    exit(1)

# Función para enviar comandos a la Arduino
def set_thruster(thruster_num, pwm_value):
    cmd = f"T{thruster_num}:{pwm_value}\n"
    arduino.write(cmd.encode())
    print(f"Enviado: {cmd.strip()}")

# Función para detener todos los thrusters
def stop_all_thrusters(thruster_list):
    for t in thruster_list:
        set_thruster(t, 1500)  # PWM neutral

# Mapeo de movimientos comunes a thrusters y PWM
MOVEMENTS = {
    "forward": {"thrusters": [2,3], "pwm": 1600},
    "backward": {"thrusters": [2,3], "pwm": 1400},
    "up": {"thrusters": [5,6], "pwm": 1600},
    "down": {"thrusters": [5,6], "pwm": 1400},
    "stop": {"thrusters": [1,2,3,4,5,6,7,8], "pwm": 1500},
}

def move(movement, duration):
    if movement not in MOVEMENTS:
        print(f"Movimiento desconocido: {movement}")
        return False
    
    thrusters = MOVEMENTS[movement]["thrusters"]
    pwm = MOVEMENTS[movement]["pwm"]
    
    print(f"Ejecutando: {movement} por {duration} segundos")
    
    for t in thrusters:
        set_thruster(t, pwm)
    
    if movement != "stop":
        time.sleep(duration)
        stop_all_thrusters(thrusters)
    
    return True

def parse_commands(args):
    """Parse command line arguments into movement-duration pairs"""
    commands = []
    i = 0
    
    while i < len(args):
        if args[i] in MOVEMENTS:
            movement = args[i]
            # Check if next argument is a number (duration)
            if i + 1 < len(args):
                try:
                    duration = float(args[i + 1])
                    commands.append((movement, duration))
                    i += 2
                except ValueError:
                    # Next argument is not a number, use default duration
                    commands.append((movement, 3.0))
                    i += 1
            else:
                # Last argument, use default duration
                commands.append((movement, 3.0))
                i += 1
        else:
            print(f"Movimiento desconocido: {args[i]}")
            i += 1
    
    return commands

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Control de thrusters Hydrus - Secuencia de comandos",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Ejemplos de uso:
  python main.py forward 5 backward 3
  python main.py up 2 down 4 forward 1
  python main.py stop
  python main.py forward up 3 stop
  
Movimientos disponibles: forward, backward, up, down, stop
Si no se especifica duración, se usa 3 segundos por defecto.
        """)
    
    parser.add_argument("commands", nargs="+", 
                        help="Secuencia de comandos: movimiento [duración] ...")
    
    args = parser.parse_args()
    
    # Parse the command sequence
    command_sequence = parse_commands(args.commands)
    
    if not command_sequence:
        print("No se encontraron comandos válidos")
        sys.exit(1)
    
    print(f"Secuencia de comandos: {command_sequence}")
    print("Presiona Ctrl+C para detener en cualquier momento")
    
    try:
        for i, (movement, duration) in enumerate(command_sequence, 1):
            print(f"\n--- Comando {i}/{len(command_sequence)} ---")
            success = move(movement, duration)
            if not success:
                print("Error en comando, continuando...")
            
            # Small pause between commands (except for stop)
            if movement != "stop" and i < len(command_sequence):
                time.sleep(0.5)
        
        print("\n¡Secuencia completada!")
        
    except KeyboardInterrupt:
        print("\nInterrumpido por usuario - Deteniendo todos los thrusters")
        stop_all_thrusters(MOVEMENTS["stop"]["thrusters"])
    except Exception as e:
        print(f"\nError durante ejecución: {e}")
        stop_all_thrusters(MOVEMENTS["stop"]["thrusters"])
    finally:
        arduino.close()
        print("Puerto serie cerrado")