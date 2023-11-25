/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/24 15:58:44 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTLIST_HPP
# define CLIENTLIST_HPP

# include <iostream>
# include <map>
# include <string>

# include "utils.hpp"

# include "Client.hpp"
# include "Log.hpp"

class ClientList
{

	public:

		typedef std::map<int, Client*>::iterator		iterator;
		typedef std::map<int, Client*>::const_iterator	const_iterator;
		
	private:

		// Prevent assignment operator
		ClientList &	operator=(ClientList const &) { return (*this); }

		// Member attributes
		bool					_deleteOnRemove;
		std::map<int, Client*>	_clients;

	public:

		// Constructors & destructor
		ClientList(void);
		ClientList(ClientList const &);
		~ClientList(void);

		// Getters
		bool const &					getDeleteOnRemove(void) const;
		std::map<int, Client*> const &	getClients(void) const;

		// Setters
		void	setDeleteOnRemove(bool const & deleteOnRemove);

		// Member functions
		bool			empty(void) const;
		size_t			size(void) const;
		iterator		begin(void);
		const_iterator	begin(void) const;
		iterator		end(void);
		const_iterator	end(void) const;

		void			add(Client* client);
		void			remove(int fd);
		Client*			get(int const & fd) const;
		Client*			get(std::string const & nickname) const;
		void			clear(void);
		void			reply(std::string const & msg) const;
};

// Output stream
std::ostream &	operator<<(std::ostream & o, ClientList const & x);

#endif
