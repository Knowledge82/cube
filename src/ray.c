#include "cube.h"

void	init_ray(t_game *game, int x, t_ray *ray)
{
	double	camera_x;
	// позиция столбца на "экране камеры" от -1 до +1, 0 - центр
	// x/screen_width - нормализация в диапазон 0<->screen_width
	// умножаем на 2 для масштабирования в диапазон 0<->2
	// вычитаем 1.0 для смещения в диапазон -1<->1
	// почему -1<->1? это стандартная нормализация в компьютерной графике
	camera_x = 2.0 * x / (double)game->image->width - 1.0;

	// rayDir = dir (центр FOV) + plane * cameraX(смещение влево/вправо)
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;

	// текущая клетка карты.
	// луч начинается в клетке, где находится игрок
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	
	// случай с лучом строго вдоль оси и соответственно деления на 0
	if (ray->dir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	

	if (ray->dir_x < 0) // луч идёт ВЛЕВО
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x; // расстояние от позиции игрока до ЛЕВОЙ границы клетки
	}
	else // луч идёт ВПРАВО
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x; // расстояние от позиции игрока до ПРАВОЙ границы клетки
	}
	if (ray->dir_y < 0) // луч идёт ВВЕРХ
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y; // расстояние от позиции игрока до ВЕРХНЕЙ границы клетки
	}
	else // луч идёт ВНИЗ
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y; // расстояние от позиции игрока до НИЖНЕЙ границы клетки
	}
}

void	dda(t_game *game, t_ray *ray)// шагаем по сетке пока не найдём стену
{
	int	hit;

	hit = 0;// (флаг: нашли ли стену)
    
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			// ближе вертикальная граница -> шагаем по X
			ray->side_dist_x += ray->delta_dist_x;//обновляем расстояние дос след верт границы
			ray->map_x += ray->step_x;// двигаемся на 1 клетку по Х
			ray->side = 0;//запоминаем, что пересекли вертикальную границу
		}
		else
		{
			// ближе горизонтальная граница -> шагаем по Y
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;// горизонтальная
		}
		//Проверить границы карты (не вышли ли за пределы? чего не может быть в принципе из-за валидации карты до этого. или я хз)
		if (ray->map_x < 0 || ray->map_x >= game->map.width
			|| ray->map_y < 0 || ray->map_y >= game->map.height)
		{
			hit = 1;
			break;
		}
		//Проверить, стена ли в клетке map.grid[map_y][map_x]
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;// нашли стену
	}
	//После цикла:
	//- ray->side хранит тип пересечённой границы
	//- ray->map_x, ray->map_y — координаты клетки со стеной
}
/*
void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)  // Вертикальная стена
		ray->perp_wall_dist = (ray->map_x - player.pos_x + (1 - ray->step_x) / 2.0) / ray->dir_x;
    else  // Горизонтальная стена
		ray->perp_wall_dist = (ray->map_y - player.pos_y + (1 - ray->step_y) / 2.0) / ray->dir_y;
}

void	draw_column(t_game *game, int x, t_ray *ray)
{
		line_height = (int)(screen_height / ray->perp_wall_dist);
		draw_start = -1 * line_height / 2 + screen_height / 2;
		draw_end = line_height / 2 + screen_height / 2;
    
    3. Нарисовать потолок (от 0 до draw_start - 1):
       Залить цветом config.ceiling_color
    
    4. Нарисовать стену (от draw_start до draw_end):
       - Пока без текстур — просто цветом (например, красный или синий в зависимости от side)
       - Позже добавим текстурирование
    
    5. Нарисовать пол (от draw_end + 1 до screen_height - 1):
       Залить цветом config.floor_color
}
*/
void	render_frame(t_game *game)// отрисовываем 1 кадр
{
	int	screen_height;
	int	screen_width;
	int	x;
	t_ray	ray;

	screen_width = game->image->width;
	screen_height = game->image->height;
	x = 0;
	debug_log("=========== RENDER_FRAME: screen_width=%d, screen_height=%d =========", screen_width, screen_height);
	while (x < screen_width)
    {
		init_ray(game, x, &ray);
		if (x < 3)
			debug_log("	After init_ray: ray.dir=(%.2f, %.2f), map=(%d, %d)", ray.dir_x, ray.dir_y, ray.map_x, ray.map_y);
		dda(game, &ray);
		if (x < 3)
			debug_log("	After DDA: map=(%d, %d), side=%d", ray.map_x, ray.map_y, ray.side);
//		calculate_wall_distance(game, &ray);
//		draw_column(game, x, &ray);
		x++;
	}
	// ОТЛАДОЧНЫЙ ВЫВОД (только для центрального столбца)
	if (x == screen_width / 2)
	{
		printf("=== Центральный луч (x=%d) ===\n", x);
		printf("После DDA: map=(%d, %d), side=%d\n", ray.map_x, ray.map_y, ray.side);
		if (ray.map_x >= 0 && ray.map_x < game->map.width
			&& ray.map_y >= 0 && ray.map_y < game->map.height)
			printf("cell = '%c'\n", game->map.grid[ray.map_x][ray.map_y]);
        else
			printf("cell = OUT OF BOUNDS\n");
    }		
	debug_log("RENDER_FRAME DONE! ✅");
}

