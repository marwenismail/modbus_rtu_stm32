import serial
import time
import serial.tools.list_ports

def find_stlink_port():
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        if 'STMicroelectronics' in p.description or 'STLink' in p.description:
            return p.device
    return None

# Automatically detect the correct COM port
PORT = find_stlink_port()

if PORT is None:
    print("❌ ST-LINK VCP not found. Please check the USB connection.")
else:
    BAUDRATE = 115200
    try:
        with serial.Serial(PORT, BAUDRATE, timeout=1) as ser:
            print(f"✅ Connected to {PORT} (ST-LINK VCP)\n")
            while True:
                data = input("Enter message to send (or 'exit' to quit): ")
                if data.lower() == "exit":
                    break
                ser.write(data.encode('utf-8'))
                print("📤 Sent:", data)
                time.sleep(0.1)

    except serial.SerialException as e:
        print("⚠️ Error:", e)
