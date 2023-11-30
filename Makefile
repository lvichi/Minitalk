# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 21:17:31 by lvichi            #+#    #+#              #
#    Updated: 2023/11/23 18:34:32 by lvichi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MiniTalk

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
RM = rm -fr
FILES = *.c
OBJS = *.o
LIBFT = -L libft -l ft
#BONUS_FILES = *_bonus.c
#BONUS_OBJS = *_bonus.o

all: client server

client: $(OBJS)
	@$(CC) $(CFLAGS) client.o $(LIBFT) -o client

server: $(OBJS)
	@$(CC) $(CFLAGS) server.o $(LIBFT) -o server

$(OBJS): $(FILES)
	@make -C libft -s
	@$(CC) $(CFLAGS) -c $(FILES)

#$(BONUS_OBJS): $(BONUS_FILES)
#	$(CC) $(CFLAGS) -c $(BONUS_FILES)

clean:
	@$(RM) $(OBJS)
	@make clean -C libft -s

fclean:
	@$(RM) $(OBJS) client server
	@make fclean -C libft -s

re: fclean all

#bonus: $(BONUS_OBJS) $(OBJS)
#	$(AR) $(NAME) $(OBJS)