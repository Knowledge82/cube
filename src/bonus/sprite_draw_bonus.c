/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:06:11 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 15:28:41 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	update_sprite_animation(t_game *game)
{
	int		i;
	double	delta_time;

	delta_time = game->mlx->delta_time;
	i = 0;
	while (i < game->num_sprites)
	{
		game->sprites[i].animation_timer += delta_time;
		if (game->sprites[i].animation_timer >= 0.2)
		{
			game->sprites[i].current_frame++;
			if (game->sprites[i].current_frame >= game->sprites[i].num_frames)
				game->sprites[i].current_frame = 0;
			game->sprites[i].animation_timer = 0.0;
		}
		i++;
	}
}

static int	calc_sprite_texture_x(int x, t_sprite_view *view,
	mlx_texture_t *tex)
{
	int		tex_x;

	tex_x = (int)(256 * (x - (-view->width / 2 + view->screen_x))
			* tex->width / view->width) / 256;
	return (tex_x);
}

static int	calc_sprite_texture_y(int y, t_sprite_view *view,
	mlx_texture_t *tex)
{
	int		d;
	int		tex_y;

	d = y * 256 - HEIGHT * 128 + view->height * 128;
	tex_y = ((d * tex->height) / view->height) / 256;
	return (tex_y);
}

void	draw_sprite_column(t_game *game, t_sprite *sprite, int x,
		t_sprite_render_data *data)
{
	int				tex_x;
	int				tex_y;
	int				y;
	uint32_t		color;
	mlx_texture_t	*tex;

	tex = sprite->frames[sprite->current_frame];
	tex_x = calc_sprite_texture_x(x, data->view, tex);
	if (tex_x < 0 || tex_x >= (int)tex->width)
		return ;
	if (data->transform->transform_y >= game->z_buffer[x])
		return ;
	y = data->view->start_y;
	while (y < data->view->end_y)
	{
		tex_y = calc_sprite_texture_y(y, data->view, tex);
		if (tex_y >= 0 && tex_y < (int)tex->height)
		{
			color = get_texture_color(tex, tex_x, tex_y);
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT
				&& (color & 0xFF) > 0)
				mlx_put_pixel(game->image, x, y, color);
		}
		y++;
	}
}
