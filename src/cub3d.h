/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:02:32 by sgokcu            #+#    #+#             */
/*   Updated: 2025/02/07 17:08:34 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <X11/keysym.h>

# define CHAR ' '
# define PI		3.14159265358979323846
# define EPSILON	1e-3
# define MAX_RAY_LENGHT	100
# define PLAYER_SIZE	0.2
# define ESC_KEY 0xff1b
# define X_KEY 0x0078
# define Z_KEY 0x007a
# define O_KEY 0x006f
# define Q_KEY 0x0071
# define W_KEY 0x0077
# define E_KEY 0x0065
# define R_KEY 0x0072
# define A_KEY 0x0061
# define S_KEY 0x0073
# define D_KEY 0x0064
# define F_KEY 0x0066
# define P_KEY 0x0070
# define RIGHT_KEY 0xff53
# define LEFT_KEY 0xff51
# define UP_KEY 0xff52
# define DOWN_KEY 0xff54

typedef union u_vec2
{
	struct
	{
		float	x;
		float	y;
	};
	float	data[2];
}	t_vec2;

typedef union u_vec2i
{
	struct
	{
		int	x;
		int	y;
	};
	int	data[2];
}	t_vec2i;

typedef union u_color
{
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	};
	unsigned int	value;
}	t_color;

typedef struct s_win
{
	void	*win;
	int		width;
	int		height;
}	t_win;

typedef struct s_img
{
	void	*img;
	t_color	*data;
	int		bits_per_pixel;
	int		size_line;
	int		line_count;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void		*mlx;
	t_win		win;
	t_img		img;
	int			time;
}	t_mlx;

typedef struct s_intptr
{
	int	a;
	int	b;
	int	c;

	int	no_count;
	int	we_count;
	int	ea_count;
	int	so_count;
	int	f_count;
	int	c_count;
}	t_intptr;

typedef struct s_location
{
	int	x;
	int	y;
}	t_location;

typedef enum e_face
{
	north,
	west,
	south,
	east
}	t_face;

typedef struct s_character
{
	t_location	p_loc;
	char		direction;
}	t_character;

typedef struct s_hit
{
	t_face	face;
	t_vec2	pos;
}	t_hit;

typedef struct s_player
{
	float	move_speed;
	float	camera_speed;
	t_vec2	pos;
	t_vec2	dir;
}	t_player;

typedef struct s_raycast
{
	float	x;
	float	y;
	int		offset;
	int		step;
	float	dist;
	t_hit	hit;
}	t_raycast;

typedef struct s_main_parse
{
	char		*file_path;
	char		*so_texture_path;
	char		*we_texture_path;
	char		*ea_texture_path;
	char		*no_texture_path;
	int			f_red;
	int			f_green;
	int			f_blue;
	int			c_red;
	int			c_green;
	int			c_blue;
	char		**whole_file;
	char		**map;
	char		**cpy_sq_map;
	char		*s_line;
	t_character	ch;
	t_location	map_size;
	t_intptr	entity_counts;
}	t_main_parse;

typedef struct s_tile_map
{
	char	*tiles;
	t_vec2i	size;
}	t_tile_map;

typedef enum e_bool
{
	error = -1,
	false,
	true
}	t_bool;

typedef enum e_mlx_event
{
	KeyPress = 2,
	KeyRelease = 3,
	ButtonPress = 4,
	ButtonRelease = 5,
	MotionNotify = 6,
	Expose = 12,
	Destroy = 17
}	t_mlx_event;

typedef struct s_input
{
	t_bool	w_key;
	t_bool	a_key;
	t_bool	s_key;
	t_bool	d_key;
	t_bool	right_key;
	t_bool	left_key;
	t_bool	esc_key;
}	t_input;

typedef enum s_enums
{
	HEIGHT = 800,
	WIDTH = 800,
}	t_enums;

typedef struct s_cub3D
{
	float			coll_deg[WIDTH];
	t_hit			collisions[WIDTH];
	t_mlx			mlx;
	t_img			tex_south;
	t_img			tex_north;
	t_img			tex_west;
	t_img			tex_east;
	t_input			inputs;
	t_color			floor;
	t_color			ceiling;
	t_player		player;
	t_tile_map		map;
	t_main_parse	*p;
}	t_cub3D;

struct s_draw_hlpr
{
	t_cub3D	*cub3d;
	t_img	*tex;
	float	line_height;
	float	tex_x;
	int		index;
};

int				start_parse(char	*file_path, t_main_parse *parser_str);
char			**strdup_double(char	**str);
int				fill_map(t_main_parse *parse);
char			**cpy_sq_map(char **map, t_main_parse *parser);
void			fill_index(int i, t_main_parse *parser, char **sq_map);
int				fill_whole_file(t_main_parse *parse_struct, int fd);
int				count_lines_of_file(int fd);
int				get_max_x(char **map);
void			go_eof(t_main_parse *parse, int *i);
void			pass_blank(t_main_parse	*parse, char *trimmed, int *i);
void			pass_attributes(t_main_parse	*parse, char *trimmed, int *i);
void			free_double_pointer(char **str);
int				count_verifier(t_main_parse *parser);
int				entity_validator(t_intptr *ct);
int				component_verifier(char c);
int				char_checker(char c);
int				checker(char **map, int y, int x);
void			counterr(char *line, t_main_parse *parse);
void			pass_blank(t_main_parse	*parse, char *trimmed, int *i);
void			go_eof(t_main_parse *parse, int *i);
void			pass_attributes(t_main_parse	*parse, char *trimmed, int *i);
int				fill_map(t_main_parse *parse);
int				floor_case(char *line, t_main_parse *parse);
int				ceiling_case(char *line, t_main_parse *parse);
void			free_textures(t_main_parse *parser);
int				determine_type(char *line, t_main_parse *parse);
int				fill_textures(t_main_parse *parser);
int				north_case(char *line, t_main_parse *parse);
int				south_case(char *line, t_main_parse *parse);
int				west_case(char *line, t_main_parse *parse);
int				east_case(char *line, t_main_parse *parse);
int				check_extra_horizontally(t_main_parse *parser);
int				flf_check(char **map);
void			f_fill(t_main_parse *prs, int y, int x);
void			clean_newlines(char **map, int i);
void			reset_entity_count(t_main_parse *parse);
int				fill_rgb_values(t_main_parse *p, char **rgb, char c);
char			*get_nums(char *line, char c);
int				check_extra_map_vertical(t_main_parse *parse, int i);
int				invalid_component_check(t_main_parse *parse);
int				blank_checker(char **map);
void			free_double_pointer(char **str);
void			initialize_struct(t_main_parse *parse_struct);
int				file_name_checker(char *file_path, char *extension);
int				comma_checker(char *num_set);
int				check_if_allocated(char **rgb);
void			single_line(t_main_parse *parser);
void			trim_each(char **rgb);
int				is_all_digit(char **rgb);
int				is_all_rgb_value(t_main_parse *p);
int				get_max_x(char **map);
char			**cpy_sq_map(char **map, t_main_parse *parser);
void			set_char(t_main_parse *p, char **sq, int y, int *i);
void			copy_loop(char **sq, int y, int *i, char **map);
void			allocate_enough(t_main_parse *p,
					char **map, int max_y, char ***sq);
int				y_func(char **map, int *max_y);
void			ft_swap_int(int *a, int *b);
float			ft_rad_to_deg(float rad);
void			init_map(t_cub3D *cub3d);
void			init_2(t_main_parse *parser, t_cub3D *cub3d);
float			ft_deg_to_rad(float deg);
void			init_win(t_cub3D *cub3d);
void			mirror_tex(t_img *tex);
void			rotate_index(t_img *tex);
void			init_all(t_cub3D *cub3d, t_main_parse *parser);
int				ft_exit(void *cub3d);
int				arrange_key_press(int keycode, t_cub3D *cub3d);
int				arrange_key_release(int keycode, t_cub3D *cub3d);
t_vec2			ft_vec2_div(t_vec2 vec, float div);
t_vec2			ft_vec2_norm(t_vec2 vec);
t_vec2			ft_vec2_rot(t_vec2 vec, float deg);
t_vec2			ft_vec2_mul(t_vec2 vec, float mul);
t_vec2			ft_vec2_add(t_vec2 vec1, t_vec2 vec2);
void			player_collision(t_cub3D *cub3d, t_vec2 next_pos);
void			player_movement(t_cub3D *cub3d, t_vec2 dir);
void			rotate_camera(t_cub3D *cub3d, t_bool rotate_dir);
void			player_modify(t_cub3D *cub3d);
float			ft_vec2_magnitude(t_vec2 vec);
t_vec2			ft_vec2_sub(t_vec2	vec1, t_vec2 vec2);
void			raycast(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, t_hit *out);
void			ft_put_pixel(t_img *img, int x, int y, t_color color);
void			ceiling_floor_drawing(t_cub3D *cub3d);
t_bool			ft_vec2_equ(t_vec2 vec1, t_vec2 vec2);
float			ft_vec2_dist(t_vec2 point1, t_vec2 point2);
float			ft_lerp(float val, float min, float max);
float			ft_normalize(float val, float min, float max);
float			get_tex_y(t_img *tex, float i, float height);
t_color			*get_tex_data(t_img *tex, float tex_x);
float			ft_normalize(float val, float min, float max);
float			get_tex_y(t_img *tex, float i, float height);
t_color			*get_tex_data(t_img *tex, float tex_x);
void			free_all(t_main_parse *parser);
void			init_tex(t_cub3D *cub3d, t_img *tex, char *path);
void			vert_hit_regulator(t_raycast *ray, t_vec2 start, t_vec2 dir);
void			hori_hit_regulator(t_raycast *ray, t_vec2 start, t_vec2 dir);
void			ray_modify(t_cub3D *cub3d);
void			draw_wall_piece(t_cub3D *cub3d,
					float line_height, int index, t_face face);
void			draw_face(struct s_draw_hlpr drw);
void			draw_wall_piece(t_cub3D *cub3d,
					float lh, int index, t_face face);
t_vec2			hit_vert(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, float *dist);
t_vec2			hit_hori(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, float *dist);
void			init_player(t_cub3D *cub3d);

float			ft_vec2_magnitude(t_vec2 vec);
t_vec2			ft_vec2_sub(t_vec2	vec1, t_vec2 vec2);
t_vec2			ft_vec2_mul(t_vec2 vec, float mul);
t_vec2			ft_vec2_add(t_vec2 vec1, t_vec2 vec2);
t_vec2			ft_vec2_inv(t_vec2 vec);
t_vec2			ft_vec2_rot(t_vec2 vec, float deg);
t_vec2			ft_vec2_norm(t_vec2 vec);
t_bool			ft_vec2_equ(t_vec2 vec1, t_vec2 vec2);
float			ft_vec2_dist(t_vec2 point1, t_vec2 point2);
t_vec2			ft_vec2_div(t_vec2 vec, float div);

static const t_vec2		g_south = (t_vec2){.x = 0, .y = 1};
static const t_vec2		g_north = (t_vec2){.x = 0, .y = -1};
static const t_vec2		g_east = (t_vec2){.x = -1, .y = 0};
static const t_vec2		g_west = (t_vec2){.x = 1, .y = 0};
static const t_vec2		g_vec2_null = (t_vec2){.x = 0, .y = 0};
static const t_vec2		g_vec2_i = (t_vec2){.x = 1, .y = 0};
static const t_vec2		g_vec2_j = (t_vec2){.x = 0, .y = 1};

#endif