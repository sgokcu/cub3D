#ifndef CUB3D
#define CUB3D

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

#define CHAR ' '
# define PI		3.14159265358979323846
# define EPSILON	1e-3
# define MAX_RAY_LENGHT	100
# define PLAYER_SIZE	0.2
#  include <X11/keysym.h>
#  define ESC_KEY XK_Escape
#  define X_KEY XK_x
#  define Z_KEY XK_z
#  define O_KEY XK_o
#  define Q_KEY XK_q
#  define W_KEY XK_w
#  define E_KEY XK_e
#  define R_KEY XK_r
#  define A_KEY XK_a
#  define S_KEY XK_s
#  define D_KEY XK_d
#  define F_KEY XK_f
#  define P_KEY XK_p
#  define RIGHT_KEY XK_Right
#  define LEFT_KEY XK_Left
#  define UP_KEY XK_Up
#  define DOWN_KEY XK_Down

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
	int a;
	int b;
	int c;

	int NO_count;
	int WE_count;
	int EA_count;
	int SO_count;
	int F_count;
	int C_count;
} t_intptr;

typedef struct s_location
{
	int x;
	int y;
} t_location;

typedef struct s_character{
	t_location p_loc;
	char direction;
} t_character;

typedef enum e_face
{
	north,
	west,
	south,
	east
}	t_face;

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
	char *file_path;
	char *so_texture_path;
	char *we_texture_path;
	char *ea_texture_path;
	char *no_texture_path;
	int	f_red;
	int	f_green;
	int f_blue;
	int	c_red;
	int	c_green;
	int c_blue;
	char **whole_file;
	char **map;
	char **cpy_sq_map;
	char *s_line;
	t_character ch;
	t_location map_size;
	t_intptr entity_counts;
} t_main_parse;

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

typedef enum s_enums{
	HEIGHT = 800,
	WIDTH  = 800,
}	t_enums;

typedef struct s_cub3D
{
	t_hit		collisions[WIDTH];
	float		coll_deg[WIDTH];
	t_input inputs;
	t_mlx mlx;
	t_color floor;
	t_color ceiling;
	t_img tex_south;
	t_img tex_north;
	t_img tex_west;
	t_img tex_east;
	t_player player;
	t_tile_map map;

	t_main_parse *p;
	
} t_cub3D;


int start_parse(char* file_path, t_main_parse *parser_str);
char **strdup_double(char **str);
int	fill_map(t_main_parse *parse);
char **cpy_sq_map(char **map, t_main_parse *parser);
void fill_index(int i, t_main_parse *parser, char **sq_map);
int	fill_whole_file(t_main_parse *parse_struct, int fd);
int	count_lines_of_file(int fd);
int get_max_x(char **map);
void go_eof(t_main_parse *parse, int *i);
void pass_blank(t_main_parse* parse, char *trimmed, int *i);
void pass_attributes(t_main_parse* parse, char *trimmed, int *i);
void	free_double_pointer(char **str);
void	ft_swap_int(int *a, int *b);
/*

west east south north görüntülerinin dosya yolları, sayısı 1 tane olabilir-
renk kodları ayrı ayrı (RGB)-
**harita her şeyin altında olmak zorunda no we vs **


*/

struct s_draw_hlpr
{
	t_cub3D	*cub3d;
	t_img	*tex;
	float	line_height;
	float	tex_x;
	int		index;
};


static const t_vec2	g_south = (t_vec2){.x = 0, .y = 1};
static const t_vec2	g_north = (t_vec2){.x = 0, .y = -1};
static const t_vec2	g_east = (t_vec2){.x = -1, .y = 0};
static const t_vec2	g_west = (t_vec2){.x = 1, .y = 0};
static const t_vec2	g_vec2_null = (t_vec2){.x = 0, .y = 0};
static const t_vec2	g_vec2_i = (t_vec2){.x = 1, .y = 0};
static const t_vec2	g_vec2_j = (t_vec2){.x = 0, .y = 1};

float	ft_vec2_magnitude(t_vec2 vec);
t_vec2	ft_vec2_sub(t_vec2	vec1, t_vec2 vec2);
t_vec2	ft_vec2_mul(t_vec2 vec, float mul);
t_vec2	ft_vec2_add(t_vec2 vec1, t_vec2 vec2);
t_vec2	ft_vec2_inv(t_vec2 vec);
t_vec2	ft_vec2_rot(t_vec2 vec, float deg);
t_vec2	ft_vec2_norm(t_vec2 vec);
t_bool	ft_vec2_equ(t_vec2 vec1, t_vec2 vec2);
float	ft_vec2_dist(t_vec2 point1, t_vec2 point2);
t_vec2	ft_vec2_div(t_vec2 vec, float div);

#endif