/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:12:49 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/07 11:12:54 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// выбор текстуры в зависимости от side и направления луча
mlx_texture_t	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0) // вертикальная стена (X-стена)
	{
		if (ray->dir_x > 0)
			return (game->textures.west);// луч вправо = смотрим на западную сторону
		else
			return (game->textures.east);// луч влево = смотрим на восточную
	}
	else // горизнтальная граница (Y-стена)
	{
		if (ray->dir_y > 0)
			return (game->textures.north);// луч вниз = смотрим на северную сторону
		else
			return (game->textures.south);// луч влево = смотрим на южную
		
	}
}

// Вычисление координаты Х на текстуре (где именно на стене попали, какой столбец текстуры использовать 0-127)
int	calculate_tex_x(t_game *game, t_ray *ray, mlx_texture_t *texture)
{
	double	wall_x;// координата точки пересечения на стене
	int	tex_x;// столбец текстуры

	if (ray->side == 0) // если вертикальная стена
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else // горизонтальная
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;

	// берём только дробную часть (от 0.0 до 1.0)
	wall_x = wall_x - floor(wall_x);

	// масштабируем на ширину текстуры
	tex_x = (int)(wall_x * (double)texture->width);

	// защита от выхода за границы (на случай ошибок округления)
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

// Получение цвета пикселя из текстуры
uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	int	index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	// Защита от выхода за границы
	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (0x000000FF); // чёрный при ошибке
	// Вычисляем индекс пикселя в массиве (формат RGBA: 4 байта на пиксель)
	index = (tex_y * texture->width + tex_x) * 4;

	// извлекаем компоненты цвета
	r = texture->pixels[index + 0];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];

	// преобразуем в формат RGBA для MLX
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
