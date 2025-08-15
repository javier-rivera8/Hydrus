python3 testing.py 'front(motor 7 1600 motor 8 1600, 15s)'

arduino-cli compile --upload -p /dev/ttyACM0 --fqbn arduino:avr:mega Testing6.ino

arduino-cli monitor -p /dev/ttyACM0 -c baudrate=9600

arduino-cli core install arduino:avr

arduino-cli lib install "Servo"



# En el monitor serie, envía:
7,1600

# Deberías ver:
Motor 7 set to 1600