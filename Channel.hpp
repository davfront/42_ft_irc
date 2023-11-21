/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/21 12:57:58 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <map>
# include <set>
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
			OPERATOR,
			FOUNDER
		}	t_status;

	
	private:

		// Prevent default constructor and copy
		Channel(void) {}
		Channel(Channel const &) {}
		Channel &	operator=(Channel const &) { return (*this); }

		// Member attributes
		std::string const				_name;
		std::set<char>					_modes;
		std::string						_topic;
		std::string						_key;
		int								_limit;
		std::map<Client*, t_status>		_clientLinks;


	public:

		// Constructors & destructor
		Channel(std::string name);
		~Channel(void);

		// Getters
		std::string const &						getName(void) const;
		std::string const &						getTopic(void) const;
		std::string const &						getKey(void) const;
		int const &								getLimit(void) const;
		std::map<Client*, t_status> const &		getClientLinks(void) const;

		// Setters
		void		setTopic(std::string const & topic);
		void		setKey(std::string const & key);
		void		setLimit(int const & limit);

		// Member functions
		void		addClientLink(Client* client, t_status status);
		void		removeClientLink(Client* client);
		t_status	getClientStatus(Client* client) const;
		void		setClientStatus(Client* client, t_status status);
		bool		isClientLinked(Client* client) const;
		bool		isInvitee(Client* client) const;
		bool		isJoined(Client* client) const;
		bool		hasOperatorRights(Client* client) const;
		bool		isFounder(Client* client) const;
		size_t		getMembersCount(void) const;

		bool		hasMode(char modeKey) const;
		void		setMode(char modeKey);
		void		unsetMode(char modeKey);
		std::string	getModes(void) const;
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Channel const & x);

#endif
