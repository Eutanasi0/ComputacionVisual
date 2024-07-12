import serial
import time

# Configura el puerto serial y la velocidad en baudios (debe coincidir con el código del ESP32)
ser = serial.Serial('COM4', 115200, timeout=1)  # Asegúrate de usar el puerto correcto

# Nombre del archivo en el escritorio
file_path = r"Nombre_de_la_ruta"

# Abre el archivo en modo de escritura
with open(file_path, 'w') as file:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            if data == "Scan Complete" or data == "Scan Stopped":
                break
            file.write(data + '\n')
            print(data)  # Muestra los datos en la consola
        time.sleep(0.1)
        
ser.close()
