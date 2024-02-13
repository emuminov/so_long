NAME=so_long
OBJ=main.o

$(NAME): $(OBJ)
	make ./minilibx-linux/
	cp ./minilibx-linux/libmlx_Linux.a .
	$(CC) $(OBJ) libmlx.a -o $(NAME) -lXext -lX11 -lm -lz

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@
