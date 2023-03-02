# Webhook Server

This is a simple webhook server that can be used to receive webhooks from GitHub and run a script when a webhook is received.

## Local Development

1. Clone this repository
2. While in the root of the project, install the python dependencies with `pip install -r requirements.txt`
3. Navigate to the `software/webhooks` directory
4. Run the server with `uvicorn main:app --reload`
5. The server should now be running at `http://localhost:8000`

## Ngrok

Ngrok is a tool that allows you to expose a local server to the internet. This is useful for testing webhooks locally.

1. Download and install ngrok from [here](https://ngrok.com/download)
2. Run `ngrok http 8000`
3. Copy the https url that ngrok gives you
4. Go to your GitHub repository and go to Settings > Webhooks
5. Monitor the calls to your webhook by going to the ngrok dashboard at `http://localhost:4040`
6. Current limitations inclue only being able to use one ngrok tunnel at a time, and the tunnel will close after 2 hours of inactivity

## GitHub Webhooks

