import serial
import time

PORT = '/dev/ttyUSB0'
BAUDRATE = 115200
TIMEOUT = 1

def init_serial():
    try:
        ser = serial.Serial(PORT, BAUDRATE, timeout=TIMEOUT)
        time.sleep(2)  # esperar para que Arduino reinicie
        print("Conectado a Arduino")
        return ser
    except serial.SerialException as e:
        print(f"Error al conectar: {e}")
        return None

def send_forward_command(ser, motor1, pwm1, motor2, pwm2, duration_ms):
    # Validaciones básicas
    if not (1 <= motor1 <= 8) or not (1 <= motor2 <= 8):
        print("Motor fuera de rango (1-8)")
        return
    if not (1000 <= pwm1 <= 2000) or not (1000 <= pwm2 <= 2000):
        print("PWM fuera de rango (1000-2000)")
        return
    if duration_ms <= 0:
        print("Tiempo inválido")
        return

    cmd = f"forward {motor1} {pwm1} {motor2} {pwm2} {duration_ms}\n"
    ser.write(cmd.encode())
    print(f"Enviado: {cmd.strip()}")

    response = ser.readline().decode().strip()
    print(f"Arduino: {response}")

def test_forward():
    ser = init_serial()
    if not ser:
        return

    # Ejemplo: motor 1 y 2 a 1600 durante 2 segundos
    send_forward_command(ser, 1, 1600, 2, 1600, 2000)

    ser.close()

if __name__ == "__main__":
    test_forward()
