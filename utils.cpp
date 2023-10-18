/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:30:41 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/17 23:37:49 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string formatTime(time_t t)
{
	char		buf[128];
	struct tm	*tm;

	tm = localtime(&t);
	strftime(buf, sizeof(buf), "%a %b %d %Y at %H:%M:%S (%Z)", tm);
	return (std::string(buf));
}
