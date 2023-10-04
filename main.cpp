/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:00:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/04 13:11:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

int main(int argc, char** argv) {

	if (argc != 3) {
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	
	std::cout << "port:     " << argv[1] << std::endl;
	std::cout << "password: " << argv[2] << std::endl;
	// todo: create and start server ...

	return (0);
}
