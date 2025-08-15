#!/usr/bin/env python3
import sys
import time
import serial

USAGE = "Uso: python3 exp.py thr1 pwm1 thr2 pwm2 duracion_segundos [--port /dev/ttyACM0] [--baud 9600]"

def main():
    if len(sys.argv) < 6:
        print(USAGE)
        sys.exit(1)
    # Extraer posibles flags al final
    args = []
    port = "/dev/ttyACM0"
    baud = 9600
    i = 1
    while i < len(sys.argv):
        if sys.argv[i] == "--port":
            i += 1
            port = sys.argv[i]
        elif sys.argv[i] == "--baud":
            i += 1
            baud = int(sys.argv[i])
        else:
            args.append(sys.argv[i])
        i += 1
    if len(args) != 5:
        print(USAGE)
        sys.exit(1)

    try:
        t1 = int(args[0])
        p1 = int(args[1])
        t2 = int(args[2])
        p2 = int(args[3])
        dur = int(args[4])
    except ValueError:
        print("Argumentos deben ser enteros")
        sys.exit(1)

    line = f"{t1} {p1} {t2} {p2} {dur}\n"

    try:
        with serial.Serial(port, baudrate=baud, timeout=2) as ser:
            # Esperar READY
            start_wait = time.time()
            ready = False
            while time.time() - start_wait < 5:
                if ser.in_waiting:
                    txt = ser.readline().decode(errors="ignore").strip()
                    if txt:
                        # print("<<", txt)
                        if txt == "READY":
                            ready = True
                            break
                else:
                    time.sleep(0.05)
            if not ready:
                # Puede estar ya inicializado
                pass

            ser.write(line.encode())
            ser.flush()

            print("Comando enviado:", line.strip())
            # Esperar OK o error
            while True:
                resp = ser.readline().decode(errors="ignore").strip()
                if not resp:
                    continue
                print("Arduino:", resp)
                if resp in ("OK", "DONE") or resp.startswith("ERR") or resp == "BUSY":
                    break

            if resp != "OK":
                if resp == "DONE":
                    # Ejecutado de inmediato (dur=0?) improbable
                    sys.exit(0)
                if resp != "OK":
                    sys.exit(1)

            # Esperar DONE
            while True:
                resp2 = ser.readline().decode(errors="ignore").strip()
                if not resp2:
                    continue
                print("Arduino:", resp2)
                if resp2 == "DONE":
                    break
    except serial.SerialException as e:
        print("Error serial:", e)
        sys.exit(1)

if __name__ == "__main__":
    main()



# python3 exp.py 1 1400 2 1400 20 --port /dev/ttyACM0