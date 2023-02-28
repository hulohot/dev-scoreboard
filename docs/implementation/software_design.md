# Software Design

## Webhooks

Webhooks are a way for an application to subscribe to events that happen in the
application. When an event happens, the application will send a POST request to
the webhook's URL. The webhook's URL is configured by the application when it
subscribes to the event.

In this case, the application is the [GitHub](https://github.com) application
and the events are the creation of a new issue or pull request. The webhook's
URL is the URL of the application's server.

## GitHub Webhooks

This diagram shows the flow of a webhook from GitHub to the
application's server.

![GitHub Webhooks](images/github_webhooks.png)

The following GitHub events trigger a webhook:

    - Issue Created
    - Issue Closed
    - Push
    - Pull Request Opened
    - Pull Request Closed
