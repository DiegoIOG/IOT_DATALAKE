import serial
import json
import time
import boto3
from datetime import datetime
import os


BUCKET_NAME = "-----------------"
SERIAL_PORT = "COM4"   
BAUD_RATE = 9600
UPLOAD_INTERVAL = 60
LOCAL_FILE = "temperature_data.json"


s3 = boto3.client("s3")
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

print("Sistema iniciado...")


if not os.path.exists(LOCAL_FILE):
    with open(LOCAL_FILE, "w") as f:
        json.dump([], f)

last_upload_time = time.time()

while True:
    try:
        if ser.in_waiting > 0:
            line = ser.readline().decode("utf-8").strip()

            new_record = {
                "timestamp": datetime.now().isoformat(),
                "temperature": line
            }

            
            with open(LOCAL_FILE, "r") as f:
                data = json.load(f)

            data.append(new_record)

            
            with open(LOCAL_FILE, "w") as f:
                json.dump(data, f, indent=2)

            print("Dato guardado localmente:", new_record)

        
        if time.time() - last_upload_time >= UPLOAD_INTERVAL:

            s3.upload_file(LOCAL_FILE, BUCKET_NAME, LOCAL_FILE)

            print(" Archivo sincronizado con S3")
            last_upload_time = time.time()

        time.sleep(1)

    except Exception as e:
        print("Error:", e)