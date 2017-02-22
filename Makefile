.PHONY: libft minilibx

SRCS = draw.c \
	   keyboard.c \
	   hook.c \
		 raytrace.c \
		 vector/vector.c \
		 intersect.c \
		 object.c \
		 color.c \
	   main.c \
	   light.c \
		 matrix.c

NAME = rtv1
GCC_FLAG = -Wall -Werror -Wextra -g
CC = gcc $(GCC_FLAG)

OBJS = $(SRCS:.c=.o)

all: libft minilibx $(NAME)

libft:
	make -C ./libft/

minilibx:
	make -C ./minilibx/

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -Lminilibx/ -lmlx -framework OPENGL -framework Appkit -Llibft -lft

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx/ clean

re: fclean all
