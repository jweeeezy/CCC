# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 19:58:11 by jwillert          #+#    #+#              #
#    Updated: 2023/04/04 20:38:27 by jwillert         ###   ########           #
#                                                                              #
# **************************************************************************** #

NAME						=	$(LEVEL1) $(LEVEL2) $(LEVEL3)
LEVEL1						=	exec_level1
LEVEL2						=	exec_level2
LEVEL3						=	exec_level3

#	Directories
LIBALLME_DIR				=	./liballme/
LIBFT_DIR					=	$(LIBALLME_DIR)libft/
LIBFT						=	$(LIBFT_DIR)libft.a
LIBFT_MANDATORY				=	$(LIBFT_DIR)libft_m.a
LIBFT_BONUS					=	$(LIBFT_DIR)libft_b.a
LIBFT_INCLUDE				=	$(LIBFT_DIR)include/
LIBME_DIR					=	$(LIBALLME_DIR)libme/
LIBME						=	$(LIBME_DIR)libme.a
LIBME_INCLUDE				=	$(LIBME_DIR)include/
FT_PRINTF_DIR				=	$(LIBALLME_DIR)ft_printf/
FT_PRINTF					=	$(FT_PRINTF_DIR)libftprintf.a
FT_PRINTF_INCLUDE 			=	$(FT_PRINTF_DIR)include/
GNL_DIR						=	$(LIBALLME_DIR)get_next_line/
GNL							=	$(GNL_DIR)libgnl.a
GNL_INCLUDE					=	$(GNL_DIR)include/

#	Files
LIBALLME					=	$(LIBALLME_DIR)liballme.a
SRC_FILES					=	utils.c

#	General rules
REMOVE						=	rm -f
CC							=	cc
CFLAGS						=	-Wall -Wextra -Werror
INCLUDE						=	-I$(LIBFT_INCLUDE) \
								-I$(LIBME_INCLUDE) \
								-I$(FT_PRINTF_INCLUDE) \
								-I$(GNL_INCLUDE)

.DELETE_ON_ERROR:

#	General targets:

.PHONY:									all liballme clean fclean re ref

all:									$(LEVEL1) $(LEVEL2) $(LEVEL3)
$(LEVEL1):								$(LIBALLME)
											$(CC) $(CFLAGS) $(INCLUDE)\
											-L$(LIBALLME_DIR) -lallme\
											$(SRC_FILES) 1.c $(LIBALLME)\
											-o $(LEVEL1)
$(LEVEL2):								$(LIBALLME)
											$(CC) $(CFLAGS) $(INCLUDE)\
											-L$(LIBALLME_DIR) -lallme\
											$(SRC_FILES) 2.c $(LIBALLME)\
										   	-o $(LEVEL2)
$(LEVEL3):								$(LIBALLME)
											$(CC) $(CFLAGS) $(INCLUDE)\
											-L$(LIBALLME_DIR) -lallme\
											$(SRC_FILES) 3.c $(LIBALLME)\
										   	-o $(LEVEL3)
$(LIBALLME):
											$(MAKE) -C $(LIBALLME_DIR)
clean:
											$(REMOVE) $(NAME)
											$(MAKE) clean -C $(LIBALLME_DIR)
fclean:									clean
											$(MAKE) fclean -C $(LIBALLME_DIR)
											$(REMOVE) outfile
re:										fclean
											$(MAKE)
ref:
											$(REMOVE) $(NAME)
											$(MAKE)
