from fastapi import FastAPI
import requests

app = FastAPI()

ESP_IP = "192.168.4.171"  # IP address of the ESP8266
ESP_PORT = "80"  # Port of the ESP8266


@app.get("/")
async def root():
    return {"message": "Hello World"}


@app.get("/ping")
async def ping():
    """
    This is a ping endpoint that is used to verify that the webhook is
    working. It is called by the webhook service on a regular basis.
    """
    print("Pong!")
    return {"message": "pong"}


@app.post("/payload")
async def payload(payload: dict):
    """
    This is a payload endpoint that is used to receive the payload from the
    webhook service. It is called by the webhook service when a webhook is
    triggered.
    """

    print("Payload received!")
    print(payload)

    # Check if the payload is for the "dispense" event

    if check_payload(payload):
        print("Dispense event detected!")
        return await dispense()
    else:
        print("Unknown event detected!")
        return {"message": "Unknown event!"}


def check_payload(payload: dict) -> bool:
    """
    This is a check_payload function that is used to check if the payload
    is for the "dispense" event.
    The following events are supported:
    - Issue Created
    - Issue Closed
    - Push
    - Pull Request Opened
    - Pull Request Closed
    """
    if payload["event"] == "dispense":
        return True
    else:
        return False


@app.get("/heartbeat")
async def heartbeat():
    """
    This is a heartbeat endpoint that is used to verify that the connection to
    the ESP8266 is working. It calls the ESP8266 to verify that it is working.
    """
    print("Sending heartbeat to ESP8266...")

    # Try and send a request to the ESP8266
    # If the ESP8266 is not connected, handle the exception
    try:
        r = requests.get(f"http://{ESP_IP}:{ESP_PORT}/heartbeat")
        print(r)
        return {"message": r.text}
    except requests.exceptions.ConnectionError as e:
        print("Connection error!")
        print(e)
        return {"message": "Connection error!"}


@app.get("/led_on")
async def led_on():
    """
    This is a led_on endpoint that is used to turn on the LED on the ESP8266.
    It calls the ESP8266 to turn on the LED.
    """
    print("Turning on LED on ESP8266...")

    # Try and send a request to the ESP8266
    # If the ESP8266 is not connected, handle the exception
    try:
        r = requests.get(f"http://{ESP_IP}:{ESP_PORT}/led_on")
        print(r)
        return {"message": r.text}
    except requests.exceptions.ConnectionError as e:
        print("Connection error!")
        print(e)
        return {"message": "Connection error!"}


@app.get("/led_off")
async def led_off():
    """
    This is a led_off endpoint that is used to turn off the LED on the ESP8266.
    It calls the ESP8266 to turn off the LED.
    """
    print("Turning off LED on ESP8266...")

    # Try and send a request to the ESP8266
    # If the ESP8266 is not connected, handle the exception
    try:
        r = requests.get(f"http://{ESP_IP}:{ESP_PORT}/led_off")
        print(r)
        return {"message": r.text}
    except requests.exceptions.ConnectionError as e:
        print("Connection error!")
        print(e)
        return {"message": "Connection error!"}


@app.get("/led_blink")
async def led_blink():
    """
    This is a led_blink endpoint that is used to toggle the LED on the ESP8266.
    It calls the ESP8266 to toggle the LED.
    """
    print("Toggling LED on ESP8266...")

    arg = {
        "duration": 5,
    }

    # Try and send a request to the ESP8266
    # If the ESP8266 is not connected, handle the exception
    try:
        r = requests.get(f"http://{ESP_IP}:{ESP_PORT}/led_blink", params=arg)
        print(r)
        return {"message": r.text}
    except requests.exceptions.ConnectionError as e:
        print("Connection error!")
        print(e)
        return {"message": "Connection error!"}


async def dispense():
    """
    This is a dispense function that is used to dispense a treat.
    It calls the ESP8266 to dispense a treat.
    """
    print("Dispensing treat...")

    arg = {
        "duration": 2,
    }

    # Try and send a request to the ESP8266
    # If the ESP8266 is not connected, handle the exception
    try:
        r = requests.get(f"http://{ESP_IP}:{ESP_PORT}/dispense", params=arg)
        print(r)
        return {"message": r.text}
    except requests.exceptions.ConnectionError as e:
        print("Connection error!")
        print(e)
        return {"message": "Connection error!"}
