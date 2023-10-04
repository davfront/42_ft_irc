# Sockets

[socket_explanation](https://docs.freebsd.org/en/books/developers-handbook/sockets/)

## Socket progamming

- Creating a socket: by specifying the domain (IPv4, IPv6), socket type (stream or datagram), and protocol (usually set to 0 for the default protocol)
- Binding: for a server socket, you bind it to a specific IP address and port number on which it will listen for incoming connections
- Listening: for server sockets, you put them into a listening state, waiting for incoming connection requests
- Accepting: when a client connects to a server, the server accepts the connection request and creates a new socket dedicated to that client
- Sending & receiving data: both client and server sockets can send and receive data over their respective connections
- Closing sockets: after communication is complete, sockets are closed to release network resources

## Socket programming to implement an IRC system

### IRC Server

- Socket initialization: the IRC server uses socket programming to create and manage server sockets. It typically listens on a specific port (usually port 6667 for non-secure connections)
- Binding & listening: the server binds to a specific IP address and port, putting the server socket into a listening state. This allows clients to connect to the server
- Accepting connections: when a client attempts to connect, the server uses the accept() function to accept incoming connections. A new socket is created for each client, and this socket is used for communication with that client
- Handling multiple clients: the server can use multi-threading or asynchronous I/O (non-blocking sockets) to handle multiple clients concurrently, each with its own socket. This allows many users to participate in the chat simultaneously
- Communication with clients: the server and clients communicate by sending and receiving messages over their respective sockets. The IRC protocol specifies how messages are formatted and exchanged. Messages may include user commands, chat messages, and server responses
- Data processing: the server processes messages from clients, maintains a list of connected users, manages channels, and enforces server rules and policies. It broadcasts messages to users in channels and handles private messages

### IRC Client

- Socket initialization: the IRC client uses socket programming to create a socket that will connect to the IRC server. The client specifies the server's IP address or hostname and the server's port
- Connecting to the server: the client uses the connect function to establish a connection to the IRC server. Once connected, it obtains a socket for communication
- User interaction: the client allows users to interact with the server by sending IRC commands and chat messages over the socket (for ex, join channels, send messages, change their nicknames, ...)
-Receiving data: the client continuously checks the socket for incoming data from the server. This includes server responses, messages from other users, and notifications about server events
- Displaying messages: messages received from the server are displayed to the user in the client's user interface. Users can see chat messages in channels they've joined and respond accordingly
- User commands: users can issue IRC commands by typing them into the client. The client translates these commands into the appropriate IRC protocol messages and sends them to the server
- Disconnecting: users can disconnect from the server by closing the socket or sending a disconnect command to the server

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