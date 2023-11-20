# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 13:10:52 by dapereir          #+#    #+#              #
#    Updated: 2023/11/16 17:34:37 by mmaxime-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# COMMANDS

CXX					=	c++
CXXFLAGS			=	-Wall -Wextra -Werror -std=c++98
RM					=	rm -rf


# PROJECT

NAME				=	ircserv

SRCS_DIR			=	.
SRCS_FILES			=	main.cpp \
						utils.cpp \
						Server.cpp \
						Server_cmds/motd.cpp \
						Server_cmds/nick.cpp \
						Server_cmds/oper.cpp \
						Server_cmds/pass.cpp \
						Server_cmds/ping.cpp \
						Server_cmds/pong.cpp \
						Server_cmds/privmsg.cpp \
						Server_cmds/quit.cpp \
						Server_cmds/user.cpp \
						Client.cpp \
						ClientList.cpp \
						Channel.cpp \
						ChannelList.cpp \
						Command.cpp \
						Log.cpp \

SRCS 				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_DIR			=	./obj
OBJS_FILES			=	$(SRCS_FILES:.cpp=.o)
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

HEADERS_DIR			=	.
HEADERS_FILES		=	text_formatting.hpp \
						replies.hpp \
						utils.hpp \
						utils.tpp Server.hpp \
						Client.hpp \
						ClientList.hpp \
						Channel.hpp \
						ChannelList.hpp \
						Command.hpp \
						Log.hpp \

HEADERS				=	$(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))
HEADERS_INC			=	-I $(HEADERS_DIR)

.PHONY: all
all:				$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.cpp Makefile $(HEADERS)
					@mkdir -p $(@D)
					@$(CXX) $(CXXFLAGS) $(HEADERS_INC) -c $< -o $@

$(NAME):			$(OBJS)
					$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

.PHONY: clean
clean:
					$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean:				clean
					$(RM) $(NAME)

.PHONY: re
re:					fclean
					$(MAKE) all

.PHONY: debug
debug:				fclean
					$(MAKE) CXXFLAGS+=-DLOG_LVL=LOG_LVL_DEBUG

.PHONY: io
io:					fclean
					$(MAKE) CXXFLAGS+=-DLOG_LVL=LOG_LVL_IO

