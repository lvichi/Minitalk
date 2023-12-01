# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 21:17:31 by lvichi            #+#    #+#              #
#    Updated: 2023/12/01 20:56:57 by lvichi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MiniTalk

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
RM = rm -fr
FILES = client.c server.c
OBJS = client.o server.o
LIBFT = -L libft -l ft
BONUS_FILES = *_bonus.c
BONUS_OBJS = *_bonus.o

all: client server

bonus: client_bonus server_bonus

client: $(OBJS)
	@$(CC) $(CFLAGS) client.o $(LIBFT) -o client

client_bonus: $(BONUS_OBJS)
	@$(CC) $(CFLAGS) client_bonus.o utils_bonus.o $(LIBFT) -o client_bonus

server: $(OBJS)
	@$(CC) $(CFLAGS) server.o $(LIBFT) -o server

server_bonus: $(BONUS_OBJS)
	@$(CC) $(CFLAGS) server_bonus.o utils_bonus.o $(LIBFT) -o server_bonus

$(OBJS): $(FILES)
	@make -C libft -s
	@$(CC) $(CFLAGS) -c $(FILES)

$(BONUS_OBJS): $(BONUS_FILES)
	@make -C libft -s
	@$(CC) $(CFLAGS) -c $(BONUS_FILES)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@make clean -C libft -s

fclean:
	@$(RM) $(OBJS) $(BONUS_OBJS) client client_bonus server server_bonus
	@make fclean -C libft -s

re: fclean all

re_bonus: fclean bonus
