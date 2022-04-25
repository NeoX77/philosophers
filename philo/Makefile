# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 11:30:00 by wdebotte          #+#    #+#              #
#    Updated: 2022/04/25 14:40:18 by wdebotte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# => TEXT
################################################################################

END		= \033[0m
BOLD	= \033[1m

RED		= \033[91m
GREEN	= \033[92m
YELLOW	= \033[93m
CYAN	= \033[96m

################################################################################
# => VARIABLES
################################################################################

NAME		= philo

PATHSRCS	= ./srcs/
PATHNULL	= /dev/null

SRCS		= ${PATHSRCS}main.c \
			${PATHSRCS}utils.c \
			${PATHSRCS}init.c

OBJS		= ${SRCS:.c=.o}
HEADERS		= ./philosophers.h

CC			= clang
CFLAGS		= -Wall -Wextra -Werror
THREAD		= -pthread 
#THREAD		= -pthread -fsanitize=thread
INCS		= -I.

RM			= rm -rf

NORM		= norminette
FLAGC		= -R CheckForbiddenSourceHeader
FLAGH		= -R CheckDefine

################################################################################
# => RULES
################################################################################

.c.o:
				@echo "${BOLD}${YELLOW}Compiling:${END}\t$<"
				@${CC} ${THREAD} ${CFLAGS} ${INCS} -c $< -o ${<:.c=.o} >${PATHNULL}

all:		${NAME}

${NAME}:	${OBJS}
				@echo "${BOLD}${GREEN}Building:${END}\t${NAME}"
				@${CC} ${THREAD} ${OBJS} ${INCS} -o ${NAME} >${PATHNULL}

clean:
				@echo "${BOLD}${RED}Removing:${END}\tAll .o files"
				@${RM} ${OBJS} >${PATHNULL}

fclean:		clean
				@echo "${BOLD}${RED}Removing:${END}\t${NAME}"
				@${RM} ${NAME} >${PATHNULL}

norminette:
				@echo "${BOLD}${YELLOW}Norminette:${END}\tAll .c files"
				${NORM} ${FLAGC} ${SRCS}
				@echo "${BOLD}${GREEN}Norminette:${END}\tOK !\n"
				@echo "${BOLD}${YELLOW}Norminette:${END}\tAll .h files"
				${NORM} ${FLAGH} ${HEADERS}
				@echo "${BOLD}${GREEN}Norminette:${END}\tOK !"

re:			fclean all

.PHONY:		all clean fclean norminette re

################################################################################
