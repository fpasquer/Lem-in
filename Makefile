#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By:  <>                                        +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/03/05 15:21:15 by                   #+#    #+#             *#
#*   Updated: 2016/05/08 12:11:23 by fpasquer         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRCS = main.c lem_in.c graphe.c graphe2.c tube.c print_lem_in.c sort.c \
	   move.c move2.c

HEADS = lem_in.h

LIBS = libft/libft.a

OTHERS = libft Makefile auteur sujet1.map sujet2.map sujet3.map bigmap.map

OBJS = $(SRCS:.c=.o)

NAME = lem-in

LOGFILE = $(LOGPATH) `date +'%d/%m/%y %H:%M:%S'`

all : $(NAME)

$(NAME):
	make -C libft/ all
	$(CC) -c -g $(FLAGS) $(SRCS)
	$(CC) $(FLAGS) -o $(NAME) -g $(OBJS) $(LIBS)

clean : $(OBJS)
	rm -rf $(OBJS)

fclean : clean
	make -C libft/ fclear
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM

push : fclean
	git add $(SRCS) $(HEADS) $(OTHERS)
	git commit -m "$(LOGFILE)"
	git push

re : fclean all

exe : re
	./$(NAME) 0 7 1 3 2 6 8 4 9 5

.PHONY: all clean fclean re exe push
