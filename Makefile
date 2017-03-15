.PHONY: libft minilibx

SRCS = draw.c \
		   keyboard.c \
		   hook.c \
			 raytrace.c \
			 vector.c \
			 intersect.c \
			 object.c \
			 color.c \
		   main.c \
		   light.c \
			 ray.c \
			 parser.c \
			 matrix.c

NAME = rtv1
GCC_FLAG = #-Wall -Werror -Wextra -g
CC = gcc $(GCC_FLAG)
RM = rm -rf

SRCDIR = ./src
OBJDIR = ./obj

LIBFT = ./libft/libft.a
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	@make -C libft
	@echo $(SRC_LIB_O)

minilibx:
	make -C ./minilibx/

$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.c)
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $^

$(NAME): $(OBJS) $(LIBFT) minilibx
	$(CC) -o $(NAME) $(OBJS) -lft -L./libft/ -Lminilibx/ -lmlx -framework OPENGL -framework Appkit

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx/ clean

re: fclean all
