# Sockets

[socket_explanation](https://docs.freebsd.org/en/books/developers-handbook/sockets/)

## Socket progamming

1. Creating a socket: by specifying the domain (IPv4, IPv6), socket type (stream or datagram), and protocol (usually set to 0 for the default protocol)
2. Binding: for a server socket, you bind it to a specific IP address and port number on which it will listen for incoming connections
3. Listening: for server sockets, you put them into a listening state, waiting for incoming connection requests
4. Accepting: when a client connects to a server, the server accepts the connection request and creates a new socket dedicated to that client
5. Sending & receiving data: both client and server sockets can send and receive data over their respective connections
6. Closing sockets: after communication is complete, sockets are closed to release network resources

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
- Receiving data: the client continuously checks the socket for incoming data from the server. This includes server responses, messages from other users, and notifications about server events
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

#### struct sockaddr

sockaddr is used to represent information about a network address. It is primarily used for specifying IP addresses and port numbers when creating sockets and binding sockets to specific network addresses.

Structure used by kernel to store most addresses.

struct sockaddr {  
	unsigned char	sa_len;	=> total length  
	sa_family_t		sa_family; => address family    
	char			sa_data[14]; => actually longer; address value  
};   
#define	SOCK_MAXADDRLEN	255	=> longest possible addresses

### htonl,  htons,  ntohl, ntohs

Convert values between host and network byte order

lib: netinet/in.h  
uint32_t htonl(uint32_t hostlong);  
uint16_t htons(uint16_t hostshort);  
uint32_t ntohl(uint32_t netlong);  
uint16_t ntohs(uint16_t netshort);  

These routines convert 16 and 32 bit quantities	between network byte order and host	byte order. On machines which have a byte order which is the same as the network order, routines are defined as null macros.  
These routines are most often used in conjunction with Internet addresses and ports as returned by gethostbyname(3) and getservent(3).

### setsockopt

lib: sys/socket.h + sys/type.h  
int	setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
- sockfd: the fd of the socket we want to modify
- level: protocol level 

### bind (server function)



### listen (server function)



### accept (server function)



### connect (client function)

int connect(int fd, const struct sockaddr *name, socklen_t namelen)
- fd returned by socket()
- name = pointer to a structure containing info about a network address
- namelen = size of the sockaddr struct

### send



### recv