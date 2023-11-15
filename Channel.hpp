/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/15 10:20:42 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <map>
# include <string>

# include "utils.hpp"

# include "Client.hpp"
# include "ClientList.hpp"
# include "Log.hpp"

class Channel
{

	public:
		typedef enum e_status {
			UNKNOWN,
			INVITEE,
			MEMBER,
			OPERATOR
		}	t_status;
		
	private:

		// Prevent default constructor and copy
		Channel(void) {}
		Channel(Channel const &) {}
		Channel &	operator=(Channel const &) { return (*this); }

		// Member attributes
		std::string const				_name;
		std::string						_topic;
		bool							_isInviteOnly;
		std::map<Client*, t_status>		_clientLinks;

	public:
	

		// Constructors & destructor
		Channel(std::string name, std::string topic = "", bool isInviteOnly = false);
		~Channel(void);

		// Getters
		std::string const &		getName(void) const;
		std::string const &		getTopic(void) const;
		bool const &			getIsInviteOnly(void) const;

		// Setters
		void	setTopic(std::string const & topic);
		void	setIsInviteOnly(bool const & isInviteOnly);
		void	setClientStatus(Client* client, t_status status);

		// Member functions
		void		addClientLink(Client* client, t_status status);
		void		removeClientLink(Client* client);
		t_status	getClientStatus(Client* client) const;
		bool		isClientLinked(Client* client) const;
		bool		isInvitee(Client* client) const;
		bool		isMember(Client* client) const;
		bool		isOperator(Client* client) const;
		size_t		getMembersCount(void) const;
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Channel const & x);

#endif
