/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2024/11/29 19:20:14 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_deg_to_rad(float deg)
{
	return ((deg / 180) * PI);
}

float	ft_rad_to_deg(float rad)
{
	return (rad * (180 / PI));
}

void init_map(t_cub3D *cub3d)
{
	cub3d->map.size.x = cub3d->p->map_size.x;
	cub3d->map.size.y = cub3d->p->map_size.y;
	cub3d->map.tiles = cub3d->p->s_line;
	if (cub3d->map.tiles == NULL)
	{
		printf("cub3d: MLX Texture Error\n"); // free
		exit(EXIT_FAILURE);
	}
}

static void	init_player(t_cub3D *cub3d)
{
	cub3d->player.pos.x = (float)cub3d->p->ch.p_loc.x + 0.5;
	cub3d->player.pos.y = (float)cub3d->p->ch.p_loc.y + 0.5;
	if (cub3d->p->ch.direction == 'S')
		cub3d->player.dir = g_south;
	if (cub3d->p->ch.direction == 'N')
		cub3d->player.dir = g_north;
	if (cub3d->p->ch.direction == 'E')
		cub3d->player.dir = g_east;
	if (cub3d->p->ch.direction == 'W')
		cub3d->player.dir = g_west;
	cub3d->player.move_speed = 0.05;
	cub3d->player.camera_speed = 1;
}

void	init_win(t_cub3D *cub3d)
{
	if (cub3d->mlx.mlx == NULL)
	{
		printf("cub3d: MLX Error\n");
		// parser freelemeleri
		exit(EXIT_FAILURE);
	}
	cub3d->mlx.win.height = HEIGHT;
	cub3d->mlx.win.width = WIDTH;
	cub3d->mlx.win.win = mlx_new_window(cub3d->mlx.mlx,
			WIDTH, HEIGHT, "cub3d - game");
	if (cub3d->mlx.win.win == NULL)
	{
		printf("cub3d: MLX Win Error\n");
		//parser freeler
		exit(EXIT_FAILURE);
	}
	cub3d->mlx.img.img = mlx_new_image(cub3d->mlx.mlx,
			cub3d->mlx.win.width, cub3d->mlx.win.height);
	cub3d->mlx.img.data = (t_color *)mlx_get_data_addr(cub3d->mlx.img.img,
			&cub3d->mlx.img.bits_per_pixel,
			&cub3d->mlx.img.size_line, &cub3d->mlx.img.endian);
	cub3d->mlx.img.size_line /= 4;
}

void	mirror_tex(t_img *tex)
{
	int	i;
	int	j;

	j = 0;
	while (j < tex->size_line)
	{
		i = 0;
		while (i < tex->line_count / 2)
		{
			ft_swap_int((int *)(&tex->data[j + (i * tex->size_line)].value),
				(int *)(&tex->data[j + ((tex->size_line - i - 1)
						* tex->size_line)].value));
			i++;
		}
		j++;
	}
}

void	rotate_index(t_img *tex)
{
	int	i;
	int	j;

	i = 0;
	while (i < tex->size_line)
	{
		j = i;
		while (j < tex->line_count)
		{
			ft_swap_int((int *)(&(tex->data[j + (tex->size_line * i)].value)),
				(int *)(&(tex->data[i + (tex->line_count * j)].value)));
			j++;
		}
		i++;
	}
}

static void	init_tex(t_cub3D *cub3d, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, path,
			&tex->size_line, &tex->line_count);
	if (tex->img == NULL)
	{
		printf("cub3d: MLX Texture Error\n");
		//parse için burada freelemeleri yap
		exit(EXIT_FAILURE);
	}
	tex->data = (t_color *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	tex->size_line /= (tex->bits_per_pixel / 8);
	rotate_index(tex);
}

void init_all(t_cub3D *cub3d, t_main_parse *parser)
{
	cub3d->p = parser;
	cub3d->inputs = (t_input){0};
	cub3d->mlx.mlx = mlx_init();
	cub3d->floor.blue = parser->f_blue;
	cub3d->floor.red = parser->f_red;
	cub3d->floor.green = parser->f_green;
	cub3d->ceiling.blue = parser->c_blue;
	cub3d->ceiling.red = parser->c_red;
	cub3d->ceiling.green = parser->c_green;
	// INIT TEX //
	init_tex(cub3d, &cub3d->tex_west, parser->we_texture_path);
	init_tex(cub3d, &cub3d->tex_west, parser->ea_texture_path);
	init_tex(cub3d, &cub3d->tex_west, parser->so_texture_path);
	init_tex(cub3d, &cub3d->tex_west, parser->no_texture_path);
	// INIT TEX //
	mirror_tex(&cub3d->tex_north);
	mirror_tex(&cub3d->tex_east);
	init_win(cub3d);
	init_player(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win, cub3d->mlx.img.img, 0, 0);
	mlx_do_key_autorepeatoff(cub3d->mlx.mlx);
}

int	ft_exit(void *cub3d)
{
	t_cub3D	*game;

	game = (t_cub3D *)cub3d;
	mlx_destroy_window(game->mlx.mlx, game->mlx.win.win); //free modifiye et
	exit(EXIT_SUCCESS);
}

int	arrange_key_press(int keycode, t_cub3D *cub3d)
{
	if (keycode == W_KEY)
		cub3d->inputs.w_key = 1;
	if (keycode == A_KEY)
		cub3d->inputs.a_key = 1;
	if (keycode == S_KEY)
		cub3d->inputs.s_key = -1;
	if (keycode == D_KEY)
		cub3d->inputs.d_key = -1;
	if (keycode == LEFT_KEY)
		cub3d->inputs.left_key = -1;
	if (keycode == RIGHT_KEY)
		cub3d->inputs.right_key = 1;
	if (keycode == ESC_KEY)
		ft_exit(cub3d);
	return (0);
}

int	arrange_key_release(int keycode, t_cub3D *cub3d)
{
	if (keycode == W_KEY)
		cub3d->inputs.w_key = 0;
	if (keycode == A_KEY)
		cub3d->inputs.a_key = 0;
	if (keycode == S_KEY)
		cub3d->inputs.s_key = 0;
	if (keycode == D_KEY)
		cub3d->inputs.d_key = 0;
	if (keycode == LEFT_KEY)
		cub3d->inputs.left_key = 0;
	if (keycode == RIGHT_KEY)
		cub3d->inputs.right_key = 0;
	return (0);
}

t_vec2	ft_vec2_div(t_vec2 vec, float div)
{
	t_vec2	vec_res;

	if (div == 0)
		return ((t_vec2){.x = 0, .y = 0});
	vec_res.x = vec.x / div;
	vec_res.y = vec.y / div;
	return (vec_res);
}

t_vec2	ft_vec2_norm(t_vec2 vec)
{
	return (ft_vec2_div(vec, ft_vec2_magnitude(vec)));
	// vektörü vektörün büyüklüğüne bölerek normalize ediyoruz.
}

t_vec2	ft_vec2_rot(t_vec2 vec, float deg)
{
	t_vec2	res;
	float	rad;

	rad = ft_deg_to_rad(deg);
	res.x = ((vec.x * cos(rad)) - (vec.y * sin(rad)));
	res.y = ((vec.x * sin(rad)) + (vec.y * cos(rad)));
	return (res);
}

t_vec2	ft_vec2_mul(t_vec2 vec, float mul)
{
	t_vec2	vec_res;

	vec_res.x = vec.x * mul;
	vec_res.y = vec.y * mul;
	return (vec_res);
}

t_vec2	ft_vec2_add(t_vec2 vec1, t_vec2 vec2)
{
	t_vec2	vec_res;

	vec_res.x = vec1.x + vec2.x;
	vec_res.y = vec1.y + vec2.y;
	return (vec_res);
}

void	player_collision(t_cub3D *cub3d, t_vec2 next_pos)
{
	if (next_pos.x > cub3d->player.pos.x)//x+ yönünde haraket ettiyse.
	{
		if (cub3d->map.tiles[(int)(next_pos.x + PLAYER_SIZE) + ((int)cub3d->player.pos.y * cub3d->map.size.x)] != '1')
		//mapi tek satır olarak aldığımız için şu an olduğumuz yeri y ile xi çarparak buluyoruz ve duvara eşit değilse ilerliyoruz.
			cub3d->player.pos.x = next_pos.x;
	}
	else
	{
		if (cub3d->map.tiles[(int)(next_pos.x - PLAYER_SIZE)
			+ ((int)cub3d->player.pos.y * cub3d->map.size.x)] != '1')
			cub3d->player.pos.x = next_pos.x;
	}
	if (next_pos.y > cub3d->player.pos.y)
	{
		if (cub3d->map.tiles[(int)cub3d->player.pos.x
				+ ((int)(next_pos.y + PLAYER_SIZE) *cub3d->map.size.x)] != '1')
			cub3d->player.pos.y = next_pos.y;
	}
	else
	{
		if (cub3d->map.tiles[(int)cub3d->player.pos.x
				+ ((int)(next_pos.y - PLAYER_SIZE) *cub3d->map.size.x)] != '1')
			cub3d->player.pos.y = next_pos.y;
	}
}

void	player_movement(t_cub3D *cub3d, t_vec2 dir)
{
	t_vec2		next_pos;

	next_pos = ft_vec2_add(cub3d->player.pos, ft_vec2_mul(dir, cub3d->player.move_speed));
	//hareket hızıyla olduğu konumu çarptırıyo ve önceki konumuyla topluyo.
	player_collision(cub3d, next_pos);//olmamız gereken yerin duvar olup olmadığına bakıyoruz.
}

void	rotate_camera(t_cub3D *cub3d, t_bool rotate_dir)
{
	cub3d->player.dir = ft_vec2_rot(cub3d->player.dir, cub3d->player.camera_speed * rotate_dir);
}



void	player_modify(t_cub3D *cub3d)
{
	t_vec2	move_dir;
	t_bool	rotate_dir;
	t_input	inputs;

	inputs = cub3d->inputs;
	move_dir = (t_vec2){.x = inputs.a_key + inputs.d_key, .y = inputs.w_key + inputs.s_key};
	 //ikisine aynı anda basılırsa hangi tarafa ne kadar gideceğini belirlemek için.
	move_dir = ft_vec2_norm(move_dir); //gideceğimiz yerle aramızda ne kadar uzunluk olduğunu buluyoruz ve 
	//bunu normalize edip 0-1 arasında tutuyoruz.
	move_dir = ft_vec2_rot(move_dir, ft_rad_to_deg(-atan2(cub3d->player.dir.x, cub3d->player.dir.y)));
	//oyuncunun baktığı yönün açısını buluyoruz sonra döndürürken bu açıyı kullanarak çarpım yapıyoruz.
	//oyuncuyu sağa döndürmek istiyosak negatif açı gerekir sola pozitif aslında saat yönünde döndürmemizi sağlar.
	rotate_dir = inputs.left_key + inputs.right_key;
	rotate_camera(cub3d, rotate_dir);
	player_movement(cub3d, move_dir);
}

static void	vert_hit_regulator(t_raycast *ray, t_vec2 start, t_vec2 dir)
{
	if (dir.x < 0)//burda 1 1 gidiyoruz arttırarak ama solunu kontrol ederken -1 diyerek kontrol etmemiz gerekir.
	{
		ray->x = (int)start.x;
		ray->step = -1;
		ray->offset = -1;//çarptığı duvardan bir sonraki duvara kadar soldaki geçiyor o yüzden sola doğru gidiyosam bir eksiltmem lazım ki doğru değeri elde ediyim. 
	}
	else
	{
		ray->x = (int)start.x + 1;
		ray->step = 1;
		ray->offset = 0;// sağa doğru giderken ama zaten çarptığım duvar olmam gereken değerde o yüzden eklememe gerek yok.
	}
}

float	ft_vec2_magnitude(t_vec2 vec)
{
	t_vec2	vec_null;

	vec_null.x = 0;
	vec_null.y = 0;
	return (ft_vec2_dist(vec_null, vec));
}

t_vec2	ft_vec2_sub(t_vec2	vec1, t_vec2 vec2)
{
	t_vec2	vec_res;

	vec_res.x = vec1.x - vec2.x;
	vec_res.y = vec1.y - vec2.y;
	return (vec_res);
}

static t_vec2	hit_vert(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, float *dist)
{
	t_raycast	ray;

	vert_hit_regulator(&ray, start, dir);
	while (ray.x >= 0 && ray.x < cub3d->map.size.x)
	{
		ray.y = ((dir.y / dir.x) * (ray.x - start.x)) + start.y;//xini biliyoruz ama ysini bilmemiz lazım tam hesaplayabilmek için o yüzden doğrunun üzerinden xi bilinen noktanın ysini bulma denklemini kullanıyoruz.
		ray.hit.pos = (t_vec2){.x = ray.x, .y = ray.y};
		//bakış açımızdan çıkan ışınların çarptıkları yerleri bulmuş oluyoruz.
		*dist = ft_vec2_magnitude(ft_vec2_sub(ray.hit.pos, start));
		//baktığımız yerle ışınımızın çarptığı yer arasındaki mesafeyi buluyoruz.
		if (*dist >= MAX_RAY_LENGHT)
			break ;
		if (ray.y >= 0 && ray.y < cub3d->map.size.y)
			if (cub3d->map.tiles[(int)(ray.x + ray.offset) + ((int)ray.y * cub3d->map.size.x)] == '1')
			//çarptığımız noktanın duvar olup olmadığını kontrol eder ve duvarsa çarpma konumunu döndürür.
				return (ray.hit.pos);
		ray.x += ray.step;
	}
	return (g_vec2_null);
}

static void	hori_hit_regulator(t_raycast *ray, t_vec2 start, t_vec2 dir)
{
	if (dir.y < 0)
	{
		ray->y = (int)start.y;
		ray->step = -1;
		ray->offset = -1;
	}
	else
	{
		ray->y = (int)start.y + 1;
		ray->step = 1;
		ray->offset = 0;
	}
}

static t_vec2	hit_hori(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, float *dist)
{
	t_raycast	ray;

	hori_hit_regulator(&ray, start, dir);
	while (ray.y > 0 && ray.y < cub3d->map.size.y)
	{
		ray.x = ((dir.x / dir.y) * (ray.y - start.y)) + start.x;
		ray.hit.pos = (t_vec2){.x = ray.x, .y = ray.y};
		*dist = ft_vec2_magnitude(ft_vec2_sub(ray.hit.pos, start));
		if (*dist >= MAX_RAY_LENGHT)
			break ;
		if (ray.x > 0 && ray.x < cub3d->map.size.x)
			if (cub3d->map.tiles[(int)(ray.x) + (((int)ray.y + ray.offset)
					* cub3d->map.size.x)] == '1')
				return (ray.hit.pos);
		ray.y += ray.step;
	}
	return (g_vec2_null);
}

void	raycast(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, t_hit *out)
{
	t_vec2	vert;
	t_vec2	hori;
	float	dist_vert;
	float	dist_hori;

	dist_vert = 0;
	dist_hori = 0;
	vert = hit_vert(cub3d, start, dir, &dist_vert);//yatay yüzeyde vurduğu duvarı döndürür.
	hori = hit_hori(cub3d, start, dir, &dist_hori);//dikey yüzeyde vurduğu duvarı döndürür.
	if (dist_hori <= dist_vert)
	{
		out->pos = hori;
		if ((start.y - hori.y) < 0)//duvarı alttan mı görüyorum üstten mi onu kontrol ediyoruz.
			out->face = north;
		else
			out->face = south;
	}
	else
	{
		out->pos = vert;
		if ((start.x - vert.x) < 0)//duvarı soldan mı görüyorum sağdan mı onu kontrol ediyoruz.
			out->face = west;
		else
			out->face = east;
	}
}

static void	ray_modify(t_cub3D *cub3d)
{
	int		i;
	float	deg_step;

	i = 0;
	deg_step = -(WIDTH / 2);//soldan sağa doğru bakması için yapıyoruz.
	while (i < WIDTH)
	{
		cub3d->coll_deg[i] = ft_rad_to_deg(atan(deg_step / WIDTH));
		//şu an olduğu yerin radyan cinsinden karşılığını verir daha sonra raycastte o çizgideki çarptığı yer var mı diye bakar.
		raycast(cub3d, cub3d->player.pos, ft_vec2_rot(cub3d->player.dir, cub3d->coll_deg[i]), &cub3d->collisions[i]);
		//raycast yaparken sanki oraya bakarak pikselleri koyuyormuş gibi yapıyoruz.
		deg_step += 1;
		i++;
	}
}

void	ft_put_pixel(t_img *img, int x, int y, t_color color)
{
	img->data[x + (img->size_line * y)] = color;//tam şu an olduğumuz noktaya ulaşmamızı ve o pixeli boyamamızı sağlar.
}

void	ceiling_floor_drawing(t_cub3D *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i >= 0 && i < WIDTH)//en soldan başlayarak sağa doğru dikey olacak şekilde yukardan aşağı doğru piksel koyuyoruz.
	{
		j = 0;
		while (j >= 0 && j < HEIGHT)
		{
			if (j <= HEIGHT / 2)
				ft_put_pixel(&cub3d->mlx.img, i, j, cub3d->ceiling);
			else
				ft_put_pixel(&cub3d->mlx.img, i, j, cub3d->floor);
			j++;
		}
		i++;
	}
}

t_bool	ft_vec2_equ(t_vec2 vec1, t_vec2 vec2)
{
	if (fabs(vec1.x) - fabs(vec2.x) < EPSILON
		&& fabs(vec1.y) - fabs(vec2.y) < EPSILON)
		return (true);
	return (false);
}

float	ft_vec2_dist(t_vec2 point1, t_vec2 point2)
{
	float	dist_x;
	float	dist_y;

	dist_x = fabs(point1.x - point2.x);
	dist_y = fabs(point1.y - point2.y);
	return (sqrtf(powf(dist_x, 2) + powf(dist_y, 2)));
}

float	ft_lerp(float val, float min, float max)
{
	return ((val * (max - min)) + min);//0-1 arasındaki değerleri ekrana çizdirmek için uygun hale getiririz mesela 0-800.
}

float	ft_normalize(float val, float min, float max)
{
	if (max == min)
		return (1);
	return ((val - min) / (max - min));//0-1 arasına getirir gelen değeri.
}

float	get_tex_y(t_img *tex, float i, float height)
{
	return (ft_lerp(ft_normalize(i, 0, height), 0, tex->size_line));
	//benim line'ım 0-400 arasıysa onu onu 0-1 arasına alıyorum ki texture'ım 0-800 arasında olduğunda doğru şekilde nereye denk geliyo anlayıp çizdiriyim.
}

t_color	*get_tex_data(t_img *tex, float tex_x)
{
	return (tex->data + ((int)ft_lerp(tex_x, 0, tex->size_line) * tex->size_line));
	//işlem yapacağımız dikey satırı döndürür.
}

static void	draw_face(struct s_draw_hlpr drw)
{
	int		i;
	float	tex_y;
	float	full_height;
	t_color	*data;

	data = get_tex_data(drw.tex, drw.tex_x);
	i = 0;
	tex_y = 0;
	full_height = drw.line_height;
	if (drw.line_height > HEIGHT)
		drw.line_height = HEIGHT;
	while (i < drw.line_height)
	{
		if (full_height > HEIGHT)
			tex_y = get_tex_y(drw.tex, i + ((full_height - HEIGHT) / 2), full_height);
		else
			tex_y = get_tex_y(drw.tex, i, drw.line_height);
		if (tex_y >= drw.tex->size_line)
			tex_y = drw.tex->size_line - 1;//taştığı kısımı almasın diye bir azaltıyoruz.
		ft_put_pixel(&drw.cub3d->mlx.img, drw.index, i + (HEIGHT - drw.line_height) / 2, data[(int)tex_y]);//aslında yukarıda ne kadar mesafe bırakacağımıza bakıyoruz ikiye bölüyoruz ki hem altta hem üstte eşit boşuk olsun ekranı ortalasın.
		i++;
	}
}

static void	draw_wall_piece(t_cub3D *cub3d, float line_height, int index, t_face face)
{
	float	pos_x;
	float	pos_y;

	pos_x = cub3d->collisions[index].pos.x;
	pos_y = cub3d->collisions[index].pos.y;
	if (face == south)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_south,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == west)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_west,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y});//kuzey ve güneyde yatay yani xe bakarız doğu ve batıda dikey yani ylere bakarız.
	if (face == north)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_north,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == east)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_east,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y});//ışının çarptığı yeri çizdirmek için 0 ve 1 arasındaki (textteki pikselin tam o noktasının şeridini çizer).
}

void	wall_drawing(t_cub3D *cub3d)
{
	float	line_height;
	float	ray_len;
	int		i;

	i = 0;
	while (i < HEIGHT)
	{
		if (ft_vec2_equ(cub3d->collisions[i].pos, g_vec2_null))
		//bir yere çarpıp çarpmadığımızı kontrol ediyoruz (float 0 değerini döndürmüyor genellikle o yüzden hata payıyla yani epsilonla kontrol ediyoruz).
		{
			i++;
			continue ;
		}
		ray_len = ft_vec2_dist(cub3d->collisions[i].pos, cub3d->player.pos);//duvar ve oyuncumuz arasındaki meesafeyi buluyoruz.
		line_height = HEIGHT / (ray_len * cos(ft_deg_to_rad(cub3d->coll_deg[i])));//balık gözünü engellemek için yapıyoruz cos yazarak dik açı gibi oluyo.
		draw_wall_piece(cub3d, line_height, i, cub3d->collisions[i].face);
		i++;
	}
}

int	modify(void *param)
{
	t_cub3D  *cub3d;

	cub3d = (t_cub3D *)param;
	player_modify(cub3d);
	ray_modify(cub3d);
	ceiling_floor_drawing(cub3d);
	wall_drawing(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	return (0);
}

void cub3d(char **av)
{
	t_main_parse parser;
	t_cub3D cub3d;
	if (!start_parse(av[1], &parser))
	{
		ft_putstr_fd("Parse Error\n", 2);
		exit(0);
	}
	init_all(&cub3d, &parser);
	mlx_hook(cub3d.mlx.win.win, \
		KeyPress, (1 << 0), arrange_key_press, &cub3d);
	mlx_hook(cub3d.mlx.win.win, \
		KeyRelease, (1 << 1), arrange_key_release, &cub3d);
	mlx_hook(cub3d.mlx.win.win, \
		Destroy, (1 << 17), ft_exit, &cub3d);
	mlx_loop_hook(cub3d.mlx.mlx, modify, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
	printf("selam\n");

	free(parser.file_path);
	free_double_pointer(parser.whole_file);
	free(parser.no_texture_path);
	free(parser.ea_texture_path);
	free(parser.we_texture_path);
	free(parser.so_texture_path);
	free_double_pointer(parser.map);
	free_double_pointer(parser.cpy_sq_map);
	return;

}

int main(int ac, char **av)
{
	if (ac == 2)
		cub3d(av);
	else
		ft_putstr_fd("Invalid argument count\n", 2);
}