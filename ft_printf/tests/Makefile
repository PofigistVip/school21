# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: larlyne <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/28 13:17:43 by larlyne           #+#    #+#              #
#    Updated: 2019/04/28 13:20:28 by larlyne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STESTNAME=stest
INC=../includes
LIBFT=../lib/libft
SRC=../src/ft_printf.c \
	../src/parser.c

all: libft stest

libft:
	@make -C $(LIBFT) re

stest:
	@gcc -o $(STESTNAME) simple_test.c $(SRC) -I $(INC) -I $(LIBFT) -L $(LIBFT) -lft

.PHONY: libft stest all