/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:13:06 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/07 12:48:12 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_draw_wall(t_game *game, t_ray *ray, t_wall_draw *wall)
{
	int	draw_start_unclipped;///

	wall->line_height = (int)(game->image->height / ray->perp_wall_dist);
	draw_start_unclipped = -1 * wall->line_height / 2 + (int)game->image->height / 2;///
	wall->draw_start = draw_start_unclipped; ///
	if (wall->draw_start < 0)
		wall->draw_start = 0; // обрезаем по верхней границе экрана
	if (draw_start_unclipped >= 0)//  если ничего не обрезано
		wall->clipped_top = 0;
	else
		wall->clipped_top = wall->draw_start - draw_start_unclipped;//запоминаем сколько было отрезано сверху
	wall->draw_end = wall->line_height / 2 + (int)game->image->height / 2;
	if (wall->draw_end >= (int)game->image->height)
		wall->draw_end = (int)game->image->height - 1; // обрезаем по нижней границе экрана
	wall->current_texture = select_texture(game, ray);
	wall->tex_x = calculate_tex_x(game, ray, wall->current_texture);
}

void	draw_ceiling(t_game *game, int x, int draw_start)// рисуем потолок
{
	int		y;
	uint32_t	ceiling_color;

	ceiling_color = (game->config.ceiling_color << 8) | 0xFF;
	y = 0;
	while (y < (int)draw_start)
	{
		mlx_put_pixel(game->image, x, y, ceiling_color);
		y++;
	}
}

void	draw_floor(t_game *game, int x, int draw_end)// рисуем пол
{
	int		y;
	uint32_t	floor_color;

	floor_color = (game->config.floor_color << 8) | 0xFF;
	y = draw_end + 1;
	while (y < (int)game->image->height)
	{
		mlx_put_pixel(game->image, x, y, floor_color);
		y++;
	}
}

/* 
 Как сопоставить пиксели экрана и текстуры? Через масштабирование (пропорциональное сопоставление)
 Математика масштабирования: 
 Для пикселя экрана y (от draw_start до draw_end):
    1. Вычислить "позицию" на стене (от 0.0 до 1.0):
       position_on_wall = (y - draw_start) / line_height
       Где:
       - (y - draw_start) — смещение от верха стены (в пикселях экрана)
       - line_height — общая высота стены на экране (в пикселях)
    2. Масштабировать эту позицию на высоту текстуры:
       tex_y = position_on_wall * texture_height
       
       НО! Если вычислять position_on_wall заново для каждого пикселя через деление, это медленно (деление — дорогая операция).
Решение: Вычислить шаг (step) — на сколько сдвигаться по текстуре за один пиксель экрана.
*/ 
void	draw_wall(t_game *game, int x, t_wall_draw *wall)// рисуем один вертикальный столбец текстурированной стены от draw_start до draw_end
{
	int	y; //текущий пиксель экрана (по вертикали)
	double	step;//масштаб: сколько пикселей текстуры на пиксель стены
	double	tex_pos;//текущая позиция на текстуре
	int	tex_y;//текущая строка текстуры (0..127)
	uint32_t	color;//цвет пикселя текстуры

	//вычисляем шаг
	step = (double)wall->current_texture->height / (double)wall->line_height;
	
	tex_pos = wall->clipped_top * step;//(было до правки)0.0 начальная позиция на текстуре. верх стены = верх текстуры. 
	//и это охуенно работает, но только если стена полностью помещается на экране от draw_start до draw_end. 
	//но вот если игрок близко к стене, то начинать надо не с верха текстуры (tex_pos = 0.0), 
	// а с ТОЙ СТРОКИ, которая реально видна на экране. Иначе искажение текстуры.
	
	//цикл по всем пикселям стены на экране (от верха до низа)
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		tex_y = (int)tex_pos;

		// защита от выхода за границы текстуры
		// на случай ошибок округления или если tex_pos >= texture_height
		if (tex_y >= (int)wall->current_texture->height)
			tex_y = wall->current_texture->height - 1;

		// получаем цвет пикселя текстуры по координатам (tex_x, tex_y)
		color = get_texture_color(wall->current_texture, wall->tex_x, tex_y);

		// рисуем пиксель на экране в позиции (x, y)
		mlx_put_pixel(game->image, x, y, color);

		//сдвигаемся на след строку текстуры
		tex_pos = tex_pos + step;

		// переходим к след пикселю экрана (вниз на 1 пиксель)
		y++;
	}
}

void	draw_column(t_game *game, int x, t_ray *ray)
{
	t_wall_draw	wall;

	init_draw_wall(game, ray, &wall);
	draw_ceiling(game, x, wall.draw_start);
	draw_wall(game, x, &wall);
	draw_floor(game, x, wall.draw_end);
}
