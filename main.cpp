/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:00:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/06 13:53:58 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <stdexcept>

void	handleStop(int signal) {
	Server::receivedSignal = signal;
}

int main(int argc, char** argv) {

	if (argc != 3) {
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handleStop;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

	try {
		Server server(argv[1], argv[2]);
		server.start();
	} catch(std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}

	return (0);
}
