#comilation vars-----------------------------------
CC=cc
CFLAGS=-Wall -Wextra -Werror -g

#subject declarations------------------------------
NAME=so_long
MINILIBX_DIR=mlx
MINILIBX=$(MINILIBX_DIR)/libmlx_Linux.a
MINILIBX_FLAGS=-L ./mlx -lmlx -Ilmlx -lXext -lX11

FILES=main.c \
	  parse.c \
	  check_errors.c \
	  utils.c
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
	$(MAKE) -C $(MINILIBX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MINILIBX) $(LIB) -o $@ $(MINILIBX_FLAGS)

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
