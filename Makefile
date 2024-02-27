NAME=so_long
OBJ=main.o
MINILIBX=minilibx-linux/libmlx_Linux.a
FLAGS=-Wall -Wextra -Werror

$(NAME): $(OBJ)
	make ./minilibx-linux/
	$(CC) $(OBJ) $(MINILIBX) -o $(NAME) -lXext -lX11 -lm -lz

%.o: %.c
	$(CC) -c $< -o $@
