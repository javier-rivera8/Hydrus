import serial
import time
import argparse

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
        return
    thrusters = MOVEMENTS[movement]["thrusters"]
    pwm = MOVEMENTS[movement]["pwm"]
    for t in thrusters:
        set_thruster(t, pwm)
    if movement != "stop":
        time.sleep(duration)
        stop_all_thrusters(thrusters)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Control de thrusters Hydrus")
    parser.add_argument("movement", type=str,
                        help="Movimiento: forward, backward, up, down, stop")
    parser.add_argument("--duration", type=float, default=3,
                        help="Duración en segundos (solo para movimientos, stop ignora)")
    args = parser.parse_args()

    try:
        move(args.movement, args.duration)
        print("Comando completado")
    except KeyboardInterrupt:
        print("Interrumpido por usuario")
        stop_all_thrusters(MOVEMENTS["stop"]["thrusters"])
    finally:
        arduino.close()
        print("Puerto serie cerrado")