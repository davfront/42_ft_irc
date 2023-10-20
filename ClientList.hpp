/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/21 01:34:55 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTLIST_HPP
# define CLIENTLIST_HPP

# include <iostream>
# include <map>
# include <string>

# include "text_formatting.hpp"

# include "Client.hpp"
# include "Log.hpp"

class ClientList
{
		
	private:

		// Prevent copy
		ClientList(ClientList const &) {}
		ClientList &	operator=(ClientList const &) { return (*this); }

		// Member attributes
		bool					_deleteOnRemove;
		std::map<int, Client*>	_clients;

	public:

		// Constructors & destructor
		ClientList(void);
		~ClientList(void);

		// Getters
		bool const &					getDeleteOnRemove(void) const;
		std::map<int, Client*> const &	getClients(void) const;

		// Setters
		void	setDeleteOnRemove(bool const & deleteOnRemove);

		// Member functions
		bool		empty(void) const;
		size_t		size(void) const;
		void		add(Client* client);
		void		remove(int fd);
		Client*		get(int const & fd) const;
		Client*		get(std::string const & nickname) const;
};

// Output stream
std::ostream &	operator<<(std::ostream & o, ClientList const & x);

#endif
