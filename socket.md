# Sockets

## Socket lifecycle

- Creating a socket: by specifying the domain (IPv4, IPv6), socket type (stream or datagram), and protocol (usually set to 0 for the default protocol)
- Binding: for a server socket, you bind it to a specific IP address and port number on which it will listen for incoming connections
- Listening: for server sockets, you put them into a listening state, waiting for incoming connection requests
- Accepting: when a client connects to a server, the server accepts the connection request and creates a new socket dedicated to that client
- Sending & receiving data: both client and server sockets can send and receive data over their respective connections
- Closing sockets: after communication is complete, sockets are closed to release network resources

## Role during IRC connection

Enables connection between IRC client and the remote IRC server:
- Establishing the connection:
	- the client uses sockets to establish a network connection to the server
	- the client socket is used to send a connection request to the server
	- the server socket listens for incoming connections from clients, once the clients establish a connection, it creates a new socket to communicate with each client
- Bidirectional communication:
	- the client socket is used to send IRC commands (joining a chanel or sending a message) to the server
	- the server socket is used to send responses and messages from the server back to the client
- Receiving messages:
	- sockets allow the client to receive messages sent by the server (responses to commands, welcome messages, messages from other users, ...)
	- the client constantly monitors the server socket for incoming data
- Sending messages: when you type messages in your IRC client, sockets are used to send those messages to the server, which then relays them to other users in the channel or to the intended recipient
- Handling disconnects:
	- the client uses sockets to notify the server of your intention to disconnect. Once the server acknowledges the disconnect, the client socket is closed

[socket_explanation](https://docs.freebsd.org/en/books/developers-handbook/sockets/)



## Functions from the subject

### socket

lib: sys/socket.h
int	socket(int domain, int type, int protocol)
- domain: specifies a communication domain (usually PF_INET for IPv4 or PF_INET6 for IPv6)
- type: specifies the communication semantics (usually SOCK_STREAM for TCP or SOCK_DGRAM for UDP)
- protocol: specifies a particular protocol to be used with the socket (usually 0 to let the system choose)

On success, a fd for the new socket is returned. -1 if error.

### bind



### listen



### accept



### connect



### send



### recv