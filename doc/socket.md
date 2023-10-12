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

### setsockopt

lib: sys/socket.h + sys/types.h  
int	setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
- sockfd: the fd of the socket we want to modify
- level: level at which the optº is defined, it can be:
	- SOL_SOCKET for socket-level optº
	- specific to a particular proto (ex: IPPROTO_TCP for TCP socket optº)
- optname = name of the socket optº we want to set
- optval = pointer to the value we want to set for the otpº
- optlen = length, in bytes, of the option value

On success, it returns 0.

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

### bind (server function)

To tell sockets which port we want to serve.

int bind(int s, const struct sockaddr *addr, socklen_t addrlen)  
- s = fd returned by socket()
- addr = pointer to a structure containing the addr info
- addrlen = size of the sockaddr struct

### listen (server function)

To prepare a socket for incoming connections

int listen( int s, int backlog )  
- s = fd of the socket that has been bound and ready to listen
- backlog = max nb of incoming connections that can be queued for processing (how many clients can wait in the queue to establish a connection)

### accept (server function)

To accept a connection on a socket.

int (int s, struct sockaddr *restrict addr, socklen_t *restrict addrlen)  
- s = fd of the socket listening for connections
- addr = pointer to a struct sockaddr that will receive the address of the client that is connecting
- addrlen = pointer to a socklen_t that contains the struct size, will be modified upon a successfull accept() to reflect the actual size of the client's address

Returns a new socket fd in case of success which will be used for communication with the client.

### connect (client function)

int connect(int s, const struct sockaddr *name, socklen_t namelen)  
- s = fd returned by socket()
- name = pointer to a structure containing info about a network address
- namelen = size of the sockaddr struct

### send

System call for sending data over a socket.

ssize_t send(int s, const void *buf, size_t len, int flags)
- s = fd on which we want to send the data
- buf = pointer to the data we want to send
- len = length of the data we want to send
- flags = additionnal flags that modify the behaviour of the function:
	- 0 for no special behaviour
	- MSG_DONTWAIT for non-blocking operation

Returns the number of bytes sent, or -1 if an error occurs.

### recv

System call for receiving data from a socket.

ssize_t recv(int s, void *buf, size_t len, int flags)
- s = fd from which we want to receive the data
- buf = pointer to the buffer where the received data will be stored
- len = max nb of bytes to receive
- flags = additionnal flags that modify the behaviour of the function:
	- 0 for no special behaviour
	- MSG_PEEK for peeking at the data w/o removing it from the socket

Returns the nb of bytes received or -1 in case of error. A return value 0 typically indicates that the remote side has close the connection.

### poll

Used for multiplexing I/O operations allowing a program to efficiently wait for events on multiple file descriptors (sockets, files, etc.) simultaneously. Can build non-blocking I/O apps.

lib: poll.h  
int poll(struct pollfd fds[], nfds_t nfds, int timeout)  
- fds = array of 'struct pollfd', where each of them describes a fd to monitor & specifies the events to watch for
- nfds = nb of elements in the fds array
- timeout = max time in ms that poll() should wait for events, -1 means indefinitely, 0 means poll and return immediately and positive specifies a timeout duration

If 1 or more fd have events ready, poll() returns the nb of fd with events. If no events occurred before the timeout, it return 0.

### fcntl (file control)

UNIX system call used for controlling various aspects of fds, including file locks or non-blocking mode.  
Versatile function that can be used to manipulate file-related properties on open file descriptors, sockets, pipes, and other I/O resources.

lib: fcntl.h  
int fcntl(int fd, int cmd, ...)
- fd = the fd on which the operation is to be performed
- cmd = arg that specifies the operation to be performed, for ex:
	- F_GETFL: get file status flags
	- F_SETFL: set file status flags
	- F_GETLK: get record locking info
	- F_SETLK: set/clear record locking info
	- F_SETLKW: set/clear record locking info, but wait if blocked
- arg = optional arg that depends on the value of cmd. For ex, when using F_SETFL, arg is a new set of flags to set.

### getprotobyname

Used to retrieve proto info based on the proto's name. This function us allows to look up the proto's entry int the system's network protc db.

lib: netdb.h  
struct protoent *getprotobyname(cont char *name)
- name = pointer to a null-terminated string containing the name of the proto we want to look up

If the proto is found, it returns a pointer to a struct protoent, which contains the proto info. If not, it returns a null pointer.

struct protoent:
- char *p_name = the official name of the proto
- char **p_aliases = a list of alternate names or aliases for the proto
- int p_proto = the proto nb