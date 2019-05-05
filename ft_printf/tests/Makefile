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

all:
	@make -C .. re
	@gcc -o $(STESTNAME) -I ../includes -I ../lib/libft simple_test.c -L .. -lftprintf

.PHONY: libft stest all