/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_formatting.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:24:17 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/04 16:24:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_FORMATTING_HPP
# define TEXT_FORMATTING_HPP

# include <iostream>

namespace Txt {
	const std::string MOVEUP = "\033[A";
	const std::string CLEAR = "\033[2K";
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";
	const std::string FAINT = "\033[2m";
	const std::string UNDERLINE = "\033[4m";
	const std::string RED = "\033[31m";
	const std::string GREEN = "\033[32m";
	const std::string YELLOW = "\033[33m";
	const std::string BLUE = "\033[34m";
	const std::string PURPLE = "\033[35m";
	const std::string CYAN = "\033[36m";
}

#endif
