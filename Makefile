$(NAME): $(OBJ)
	$(MAKE) -C ./minilibx-linux/
	$(CC) $(OBJ) $(MINILIBX) -o $(NAME) -lXext -lX11 -lm -lz

#comilation vars-----------------------------------
CC=cc
CFLAGS=-Wall -Wextra -Werror -g

#subject declarations------------------------------
NAME=so_long
MINILIBX_DIR=minilibx-linux
MINILIBX=$(MINILIBX_DIR)/libmlx_Linux.a

FILES=main.c
HEAD_FILE=so_long.h

HEAD_DIR=include
HEADER=$(HEAD_FILE:%.h=$(HEAD_DIR)/%.h)

SRCS_DIR=srcs
SRCS=$(FILES:%.c=$(SRCS_DIR)/%.c)

OBJS_DIR=objs
OBJS=$(FILES:%.c=$(OBJS_DIR)/%.o)

#libft declarations--------------------------------
LIB_DIR=libft
LIB=$(LIB_DIR)/libft.a

#rules---------------------------------------------
$(NAME): $(LIB) $(HEADER) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./minilibx-linux/
	$(CC) $(OBJ) $(MINILIBX) -o $@ -lXext -lX11 -lm -lz

$(BONUS_NAME): $(LIB) $(HEADER) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIB) -o $(BONUS_NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(SRCS) $(HEADER)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): libft

libft:
	$(MAKE) -C $(LIB_DIR)

all: $(NAME)

clean:
	$(MAKE) -C $(LIB_DIR) $@
	$(MAKE) -C $(MINILIBX_DIR) $@
	rm $(OBJS_DIR) -rf

fclean: clean
	$(MAKE) -C $(LIB_DIR) $@
	rm $(NAME) $(LIB) -f
	rm $(BONUS_NAME) $(LIB) -f

re: fclean
	$(MAKE) -C $(LIB_DIR) $@
	$(MAKE) all --no-print-directory

.PHONY: all clean fclean re libft
