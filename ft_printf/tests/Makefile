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
INC=includes

libft:
	@make -C libft

stest:
	@gcc -o $(STESTNAME) simple_test.c -I $(INC) -I libft -L libft -lft
