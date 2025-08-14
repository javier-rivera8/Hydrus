import serial
import time

arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

time.sleep(2)
print("Conectado a Arduino. Comandos: F (adelante), B (atrás), S (stop), L (izquierda), R (derecha)")
print("Escribe 'exit' para salir.")

while True:
    cmd = input(">> ").strip().upper()
    if cmd == "EXIT":
        break
    if cmd in ["F", "B", "S", "L", "R"]:
        arduino.write(cmd.encode())
    else:
        print("Comando inválido.")
