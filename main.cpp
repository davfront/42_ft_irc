/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:00:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/13 12:29:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {

	if (argc != 3) {
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	try {
		Server server(std::atoi(argv[1]), argv[2]);
	} catch(std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	if (server.init() != 0)
		exit(1);

	return (0);
}
