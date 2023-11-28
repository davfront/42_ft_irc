/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:29:59 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/28 19:45:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T>
std::string stringify(T const & x)
{
	std::stringstream ss;
	ss << x;
	return (ss.str());
}

template <typename T>
void	deleteSafe(T* & ptr) {
    if (ptr) {
        delete ptr;
        ptr = NULL;
    }
}
