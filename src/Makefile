NAME	:= fdf
CC		:= cc
SRC		:=	../get_next_line/get_next_line.c \
			../get_next_line/get_next_line_utils.c \
			colors_handling.c \
			draw_line.c \
			draw_map.c \
			fdf.c \
			gradient.c \
			image_handling.c \
			initialisations1.c \
			initialisations2.c \
			key_handling.c \
			memory_freeing1.c \
			memory_freeing2.c \
			parsing.c \
			transformations.c \
			utils1.c \
			utils2.c
CFLAGS	:= -Wall -Wextra -Werror -g
LIBS	:= ../libft/libft.a ../ft_printf/libftprintf.a
OBJ		:= $(SRC:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJ) fdf.h
	make -C ../ft_printf all
	make -C ../libft all
	$(CC) $(OBJ) $(LIBS) -lmlx -lXext -lX11 -lm -o $(NAME)

clean	:
	make -C ../ft_printf clean
	make -C ../libft clean
	rm -f $(OBJ)

fclean	:
	make -C ../ft_printf fclean
	make -C ../libft fclean
	rm -f $(OBJ) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re
