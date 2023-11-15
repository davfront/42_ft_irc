/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:29:59 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/15 09:18:36 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <cctype>
# include <ctime>
# include <sstream>
# include <string>
# include <vector>

# include "utils.tpp"

std::string                 formatTime(time_t t);
std::vector<std::string>    split(std::string const & s, std::string const & sep, bool keepEmpty = false);
std::string	                toLowerCase(std::string const & s);

#endif
