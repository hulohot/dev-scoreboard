# Webhook Server

This is a simple webhook server that can be used to receive webhooks from GitHub and run a script when a webhook is received.

## Local Development

1. Clone this repository
2. While in the root of the project, install the python dependencies with `pip install -r requirements.txt`
3. Navigate to the `software/webhooks` directory
4. Run the server with `uvicorn main:app --reload`
