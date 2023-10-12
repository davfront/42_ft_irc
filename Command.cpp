/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/12 11:47:05 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"


// Non-member functions (private)
// ==========================================================================

std::string	Command::_extractMessageToken(std::string & msg)
{
	size_t start = msg.find_first_not_of(' ');
	if (start == std::string::npos) {
		msg = "";
		return ("");
	}

	size_t end = msg.find_first_of(' ', start);
	if (end == std::string::npos) {
		std::string token = msg.substr(start);
		msg = "";
		return (token);
	}

	std::string token = msg.substr(start, end - start);
	msg = msg.substr(end);
	return (token);
}


// Constructors & destructor
// ==========================================================================

Command::Command(std::string msg)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Creating Command from message: `" << msg << "`" << Txt::RESET << std::endl;

	if (msg.size() > 510) {
		throw Command::TooLargeMessageException();
	}
	
	std::string token;

	// prefix or command
	token = Command::_extractMessageToken(msg);
	if (token[0] == ':') {
		this->_prefix = token;
	} else {
		this->_command = token;
	}
	
	// command
	if (this->_command.empty()) {
		this->_command = Command::_extractMessageToken(msg);
	}

	// parameters
	while (!msg.empty()) {
		token = Command::_extractMessageToken(msg);
		if (!token.empty()) {
			if (token[0] == ':') {
				token = token.substr(1) + msg;
				msg = "";
			}
			this->_parameters.push_back(token);
		}
	}

	// validation
	if (this->_prefix == ":" || this->_command.empty()) {
		throw Command::InvalidMessageException();
	}
	
	if (DEBUG)
		std::cout << Txt::FAINT <<  "Command " << *this << " created." << Txt::RESET << std::endl;

	return ;
}

Command::Command(Command const & src):
	_prefix(src.getPrefix()),
	_command(src.getCommand()),
	_parameters(src.getParameters())
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Command " << *this << " created (copy)." << Txt::RESET << std::endl;
	return ;
}

Command::~Command(void)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Command " << *this << " destroyed." << Txt::RESET << std::endl;
	return ;
}


// Operators
// ==========================================================================

Command &	Command::operator=(Command const & rhs)
{
	if (this != &rhs) {
		this->_prefix = rhs.getPrefix();
		this->_command = rhs.getCommand();
		this->_parameters = rhs.getParameters();
	}
	return (*this);
}


// Getters
// ==========================================================================

std::string const &	Command::getPrefix(void) const
{
	return (this->_prefix);
}

std::string const &	Command::getCommand(void) const
{
	return (this->_command);
}

std::vector<std::string> const &	Command::getParameters(void) const
{
	return (this->_parameters);
}


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, Command const & x)
{
	o << "{";
	if (!x.getPrefix().empty()) {
		o << "prefix: \"" << x.getPrefix() << "\"";
		o << ", ";
	}
	o << "command: \"" << x.getCommand() << "\"";
	o << ", ";
	o << "parameters: {";
	for (size_t i = 0; i < x.getParameters().size(); i++) {
		o << "`" << x.getParameters()[i] << "`";
		if (i < x.getParameters().size() - 1) {
			o << ", ";
		}
    }
	o << "}}";

	return (o);
}
