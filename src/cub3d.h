#ifndef CUB3D
#define CUB3D

#include <fcntl.h>
#include <stdio.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

#define CHAR ' '

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
	t_location character;
	t_location map_size;
	t_intptr entity_counts;
} t_main_parse;

typedef enum s_enums{
	HEIGHT = 800,
	WIDTH  = 800,
}	t_enums;


typedef struct	t_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*image;
}	t_mlx;


typedef struct	s_cub
{
	t_mlx	mlx;
	t_intptr intptr;
	char *pixels;
}	t_cub;

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
/*

west east south north görüntülerinin dosya yolları, sayısı 1 tane olabilir-
renk kodları ayrı ayrı (RGB)-
**harita her şeyin altında olmak zorunda no we vs **


*/
#endif