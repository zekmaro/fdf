NAME := fdf
CC := cc
SRC := fdf.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
CFLAGS := -Wall -Wextra -Werror -g
LIBS := libft/libft.a ft_printf/libftprintf.a
OBJ := $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -lmlx -lXext -lX11 -lm -o $(NAME)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re:	fclean all

.PHONY: all clean fclean re
