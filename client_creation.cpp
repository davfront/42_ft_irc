#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int	main()
{
	const char* serverIP = "192.43.244.18";
	const int	server_port = 13;

	// Socket creation

	int	client_socket;
	client_socket = socket( AF_INET, SOCK_STREAM, 0 );
	if ( client_socket == -1 )
	{
		std::cerr << "Error while creating socket" << std::endl;
		return ( 1 );
	}

	// Server address specification

	struct sockaddr_in	server_addr;
	
	bzero( &server_addr, sizeof( server_addr ) ); // initialize the struct

	server_addr.sin_family = AF_INET; // IPv4
	server_addr.sin_port = htons( server_port ); // htons = host to network short, to be sure port is well converted into the bytes order needed by the struct
	server_addr.sin_addr.s_addr = htonl( inet_addr( serverIP ) ); // inet_addr = to convert a human-readable IPv4 in dot-dec notatº into its binary representation

	// Connection to server
	if ( connect( client_socket, ( struct sockaddr* )&server_addr, sizeof( server_addr ) ) < 0 )
	{
		std::cerr << "Error: connecting to server" << std::endl;
		close( client_socket );
		return ( 2 );
	}

	std::string	msg;
	while ( 1 )
	{
		std::getline( std::cin, msg );
		std::cout << msg << std::endl;
	}

	return ( 0 );
}

