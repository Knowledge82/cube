/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:13:06 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/10 16:16:42 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_draw_wall(t_game *game, t_ray *ray, t_wall_draw *wall)
{
	int	draw_start_unclipped;

	wall->line_height = (int)(game->image->height / ray->perp_wall_dist);
	draw_start_unclipped = -wall->line_height / 2
		+ (int)game->image->height / 2;
	wall->draw_start = draw_start_unclipped;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (draw_start_unclipped >= 0)
		wall->clipped_top = 0;
	else
		wall->clipped_top = wall->draw_start - draw_start_unclipped;
	wall->draw_end = wall->line_height / 2 + (int)game->image->height / 2;
	if (wall->draw_end >= (int)game->image->height)
		wall->draw_end = (int)game->image->height - 1;
	wall->current_texture = select_texture(game, ray);
	wall->tex_x = calculate_tex_x(game, ray, wall->current_texture);
}

static void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int			y;
	uint32_t	ceiling_color;

	ceiling_color = (game->config.ceiling_color << 8) | 0xFF;
	y = 0;
	while (y < (int)draw_start)
	{
		mlx_put_pixel(game->image, x, y, ceiling_color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int draw_end)
{
	int			y;
	uint32_t	floor_color;

	floor_color = (game->config.floor_color << 8) | 0xFF;
	y = draw_end + 1;
	while (y < (int)game->image->height)
	{
		mlx_put_pixel(game->image, x, y, floor_color);
		y++;
	}
}

static void	draw_wall(t_game *game, int x, t_wall_draw *wall)
{
	uint32_t	color;
	int			y;
	int			tex_y;
	double		step;
	double		tex_pos;

	step = (double)wall->current_texture->height / (double)wall->line_height;
	tex_pos = wall->clipped_top * step;
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)wall->current_texture->height)
			tex_y = wall->current_texture->height - 1;
		color = get_texture_color(wall->current_texture, wall->tex_x, tex_y);
		mlx_put_pixel(game->image, x, y, color);
		tex_pos = tex_pos + step;
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
