#!/usr/bin/env python3
# ===============================================================
#  AWS IoT Core Publisher for ctrlX CORE
#  Author: <your name>
#  Description:
#     Reads data from ctrlX Data Layer and publishes to AWS IoT Core via MQTT (TLS)
# ===============================================================

import json
import os 
import ssl
import time
import logging
import paho.mqtt.client as mqtt
from datetime import datetime

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)
console_handler = logging.StreamHandler()
console_handler.setFormatter(logging.Formatter('[%(asctime)s] %(levelname)s - %(message)s'))
logger.addHandler(console_handler)

AWS_IOT_ENDPOINT = "a14u78rq4h2cd-ats.iot.ap-southeast-1.amazonaws.com"
AWS_IOT_PORT = 8883
AWS_IOT_TOPIC = "ctrlx/data"

CERTS_DIR = os.path.join(os.getenv("SNAP_USER_COMMON", "/tmp"), "certs")

CA_PATH = os.path.join(CERTS_DIR, "root-CA.crt")
CERT_PATH = os.path.join(CERTS_DIR, "ctrlx-edge-gateway.cert.pem")
KEY_PATH = os.path.join(CERTS_DIR, "ctrlx-edge-gateway.private.key")

class AWSPublisher:
    is_connected = False   #Static biến dùng cho API

    def __init__(self, client_id="ctrlx-core-publisher"):
        self.client_id = client_id
        self.client = mqtt.Client(client_id=self.client_id)
        self.connected = False

        # Gán callback
        self.client.on_connect = self.on_connect
        self.client.on_disconnect = self.on_disconnect
        self.client.on_publish = self.on_publish

        # Thiết lập chứng chỉ bảo mật TLS
        self.client.tls_set(
            ca_certs=CA_PATH,
            certfile=CERT_PATH,
            keyfile=KEY_PATH,
            cert_reqs=ssl.CERT_REQUIRED,
            tls_version=ssl.PROTOCOL_TLSv1_2,
            ciphers=None,
        )

        self.client.tls_insecure_set(False)

    def on_connect(self, client, userdata, flags, rc):
        if rc == 0:
            self.connected = True
            AWSPublisher.is_connected = True
            logger.info(f"✅ Connected to AWS IoT Core at {AWS_IOT_ENDPOINT}")

    def on_disconnect(self, client, userdata, rc):
        self.connected = False
        AWSPublisher.is_connected = False
        logger.warning("⚠️ Disconnected from AWS IoT Core")

    def on_publish(self, client, userdata, mid):
        logger.debug(f"📤 Message {mid} published successfully.")

    def connect(self):
        try:
            self.client.connect(AWS_IOT_ENDPOINT, AWS_IOT_PORT, keepalive=60)
            self.client.loop_start()
            # Đợi kết nối
            for _ in range(10):
                if self.connected:
                    return True
                time.sleep(0.5)
            raise TimeoutError("Could not connect to AWS IoT Core.")
        except Exception as e:
            logger.exception(f"Error while connecting: {e}")
            return False

    def publish_to_aws(self, address: str, value):
        """
        Gửi dữ liệu (từ Data Layer) lên AWS IoT Core topic.
        """
        if not self.connected:
            logger.warning("Not connected. Trying to reconnect...")
            if not self.connect():
                return False

        payload = {
            "timestamp": datetime.utcnow().isoformat(),
            "source": "ctrlX CORE",
            "node": address,
            "value": value
        }

        try:
            self.client.publish(AWS_IOT_TOPIC, json.dumps(payload), qos=1)
            logger.info(f"📡 Published to AWS IoT: {payload}")
            return True
        except Exception as e:
            logger.error(f"Failed to publish to AWS IoT: {e}")
            return False

    def stop(self):
        self.client.loop_stop()
        self.client.disconnect()
        logger.info("AWS Publisher stopped.")


if __name__ == "__main__":
    aws = AWSPublisher()

    print("\n=== AWS IoT Core Connection Test Mode ===")
    print("Nhấn CTRL + C để dừng test\n")

    try:
        if not aws.connect():
            print("❌ Không thể kết nối AWS IoT Core. Kiểm tra chứng chỉ / mạng.")
        
        while True:
            if aws.connected:
                logger.info("🔄 Still connected to AWS IoT Core")
            else:
                logger.warning("🟥 Lost connection — retrying...")
                aws.connect()

            aws.publish_to_aws("framework/metrics/cpu-utilisation-percent", 42.3)

            time.sleep(2)

    except KeyboardInterrupt:
        print("\n⛔ Test dừng bởi người dùng (CTRL + C)")

    finally:
        aws.stop()
        print("🔌 AWS Publisher stopped.\n")
