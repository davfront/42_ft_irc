#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <poll.h>
#include <vector>
#include <fcntl.h>
#include <stdio.h>

const int	max_clients = 10;

int	main()
{
	int					server_socket;
	const int 			port = 6667;
	struct sockaddr_in	sa = {};

	// Socket creation
	
	server_socket = socket( PF_INET, SOCK_STREAM, 0 );
	if ( server_socket == -1 )
	{
		perror("Error: creating socket");
		return ( 1 );
	}

	// !!!!!!!! Ajouter setsockopt() pour définir les options de la socket

	//port = 6667;

	// Struct sockaddr initialization

	sa.sin_family = PF_INET; // IPv4 format
	sa.sin_port = htons( port ); // Convert port
	sa.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

	// Binding of server socket

	if ( bind( server_socket, reinterpret_cast<struct sockaddr *>( &sa ), sizeof( sa ) ) < 0 )
	{
		perror("Error: binding server socket");
		close( server_socket );
		return ( 2 );
	}

	// Listening

	if ( listen( server_socket, SOMAXCONN ) < 0 ) // SOMAXCONN = constant representing the max size of the backlog
	{
		std::cerr << "Error: listening" << std::endl;
		close( server_socket );
		return ( 3 );
	}

	// Creating a pollfd array

		// Array of pollfd structs to monitor sockets
	std::vector<pollfd> fds( max_clients + 1 ); // including server socket
	fds[0].fd = server_socket;
	fds[0].events = POLLIN; // Monitor for incoming connections

		// Initialize other fds entries
	for( int i = 1; i <= max_clients; ++i )
	{
		fds[i].fd = -1; // -1 indicates unused
	}

	std::cout << "Server is listening on port " << port << std::endl;

	while ( true )
	{
		int ret = poll( fds.data(), fds.size(), -1 );
		if ( ret < 0 )
		{
			perror("Error: poll failed");
			break ;
		}
		for ( size_t i = 0; i < fds.size(); ++i )
		{
			if ( fds[i].revents & POLLIN )
			{
				if ( fds[i].fd == server_socket )
				{
					// new connection request
					int client_socket = accept( server_socket, nullptr, nullptr );
					if ( client_socket < 0 )
						std::cerr << "Error: accept failed" << std::endl;
					else
					{
						// set the client socket to non-blocking mode
						int flags = fcntl( client_socket, F_GETFL, 0 );
						fcntl( client_socket, F_SETFL, flags | O_NONBLOCK );

						std::cout << "New client connected" << std::endl;

						// find an empty slot in the fds array to store the client socket
						for ( size_t j = 1; j < fds.size(); ++j )
						{
							if ( fds[j].fd == -1 )
							{
								fds[j].fd = client_socket;
								fds[j].events = POLLIN;
								break ;
							}
						}
					}
				}
				else
				{
					// data available to read from a client socket
					char buffer[1024];
					int ret = recv( fds[i].fd, buffer, sizeof( buffer ), 0 );
					if ( ret <= 0 )
					{
						// connection closed or error
						close( fds[i].fd );
						fds[i].fd = -1;
						std::cout << "Client disconnected" << std::endl;
					}
					buffer[ret] = '\0';
					std::string	msg( buffer );
					std::cout << msg << std::endl;
				}
			}
		}
	}
	std::cout << "End of loop" << std::endl;
	close( server_socket );
	return ( 0 );
}