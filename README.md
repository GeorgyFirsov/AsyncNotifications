# AsyncNotifications

> Work in progress

It is an example of Client-Server application model, that demonstrates
Microsoft AsyncRPC technology in action.

This project contains two applications:
- Server app
- Client app

### Server application

After this program started it is ready to receive subscription requests from many 
clients. It receives a synchronous client RPC-call, which is an request for subscription,
register it inside itself and sends a reply for success of failure of registration. After
this action it receives an asynchronous call and leaves it pending until a specified
event happened (see more about events in [Events](#Events) section). In case of an event 
server invokes `RpcAsyncCompleteCall` to send some information about it to subscribed client.
If all client's subscriptions are cancelled asyncronous call will be aborted with `ERROR_CANCELLED`
status. In case of cancellation of a subscription server decreases an internal binded with 
concrete client counter (not to cancel asynchronous call mistakenly).

### Client application

Client will be able to subscribe to any number of distinct events. It'll wait for asyncroous
call result in a separate thread in order to allow concurrent waiting and subscribing.

### Events

In order to simplify this application events will be as simple as possible:
After minimal preparations server will wait for input with keyboard. Subscription will be a letter
which should be the first letter of servers' input string. Server will be able to handle any
number of input strings.

### Commands

Client app will have simple rules applied to it's input:
- `quit` will close client in common way with all cleaning procedures
- `exit` will terminate client immediately (by calling `ExitProcess`)
- `subscribe [a-zA-Z]` will send a subscription request to server
- `cancel [a-zA-Z]` will send a cancellation request to server
- any other string will be ignored

Server's commands will be simpler:
- `quit` will close client in common way with all cleaning procedures
- `exit` will terminate client immediately (by calling `ExitProcess`)
- any other string will be assumed as an input