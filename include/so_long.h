/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:51:11 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/08 11:30:10 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <X11/keysym.h>
# include <fcntl.h>
# define TILE_SIZE 64
# define FLOOR_TILE_PATH "./assets/floor.xpm"
# define WALL_TILE_PATH "./assets/wall.xpm"
# define PLAYER_LEFT_TILE_PATH "./assets/player_left.xpm"
# define PLAYER_RIGHT_TILE_PATH "./assets/player_right.xpm"
# define COLLECTIBLE_1_TILE_PATH "./assets/collectible_1.xpm"
# define COLLECTIBLE_2_TILE_PATH "./assets/collectible_2.xpm"
# define COLLECTIBLE_3_TILE_PATH "./assets/collectible_3.xpm"
# define ENEMY_TILE_PATH "./assets/enemy.xpm"
# define EXIT_TILE_PATH "./assets/exit.xpm"

enum				e_tokens
{
	floor_token = '0',
	wall_token = '1',
	player_token = 'P',
	collectible_token = 'C',
	exit_token = 'E',
	enemy_token = 'T',
	occupied_token = '-'
};

typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct s_tiles
{
	void			*floor;
	void			*wall;
	void			*player_left;
	void			*player_right;
	void			*player_current;
	void			*collectible_1;
	void			*collectible_2;
	void			*collectible_3;
	void			*exit;
	void			*enemy;
}					t_tiles;

typedef struct s_map
{
	t_pos			player_pos;
	t_pos			*collectibles_pos;
	char			**rows;
	int				x;
	int				y;
}					t_map;

typedef struct s_token_count
{
	int				player_count;
	int				collectible_count;
	int				exit_count;
}					t_token_count;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_tiles			tiles;
	t_token_count	token_count;
	int				player_moves_count;
	int				collected_count;
}					t_game;

void				check_exit_and_collectibles_availability(t_game *g);
void				check_exit_and_collectibles_presence(t_game *g);
void				check_filename_extension(char *file);
void				check_non_allowed_tokens(t_game *g);
void				check_walls_presence(t_game *g);
char				**clone_matrix(int l, char **matrix);
void				end_game(int is_error, char *msg, t_game *g);
int					handle_keyboard_input(int keysym, t_game *g);
void				init_mlx(t_game *g);
void				init_xpm_tiles(t_game *g);
char				**list_to_matrix(t_list *lst);
void				parse(char *file, t_game *g);
void				put_tile_to_pos(t_game *g, void *tile, t_pos pos);
void				render_initial_graphic(t_game *g);
int					render_next_frame(t_game *g);
int					safe_close(int fd, t_list *lst);
int					safe_open(char *file);

#endif
