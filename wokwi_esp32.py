import network
import time
import random
import json
from umqtt.simple import MQTTClient

# WiFi
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect("Wokwi-GUEST", "")

while not wlan.isconnected():
    time.sleep(1)

print("Connected to WiFi")

# MQTT
MQTT_BROKER = "test.mosquitto.org"  # 🔥 better broker
CLIENT_ID = "esp32-" + str(random.randint(1000, 9999))  # 🔥 unique ID
TOPIC = "health/patient/data"

client = MQTTClient(CLIENT_ID, MQTT_BROKER, keepalive=60)
client.connect()

print("Connected to MQTT Broker")
print("Publishing to topic:", TOPIC)

def generate_data():
    return {
        "patient_id": random.randint(1, 5),
        "sysBP": random.randint(110, 150),
        "diaBP": random.randint(70, 100),
        "heartRate": random.randint(60, 100),
        "glucose": random.randint(80, 150)
    }

while True:
    try:
        data = generate_data()
        msg = json.dumps(data)

        client.publish(TOPIC, msg.encode())
        print("Published:", msg)

    except Exception as e:
        print("MQTT Error:", e)

        try:
            client.disconnect()
        except:
            pass

        client.connect()
        print("Reconnected")
        time.sleep(1)

    time.sleep(8)