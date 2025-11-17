/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 21:03:46 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 16:04:06 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	calc_sprite_transform(t_game *game, t_sprite *sprite,
	t_sprite_transform *transform)
{
	double	inv_det;

	transform->sprite_x = sprite->x - game->player.pos_x;
	transform->sprite_y = sprite->y - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform->transform_x = inv_det * (game->player.dir_y * transform->sprite_x
			- game->player.dir_x * transform->sprite_y);
	transform->transform_y = inv_det * (-game->player.plane_y
			* transform->sprite_x + game->player.plane_x * transform->sprite_y);
}

static void	calc_sprite_view_data(t_sprite_transform *transform,
	t_sprite_view *view)
{
	view->screen_x = (int)((WIDTH / 2)
			* (1 + transform->transform_x / transform->transform_y));
	view->height = abs((int)(HEIGHT / transform->transform_y));
	view->width = abs((int)(HEIGHT / transform->transform_y));
}

static void	calc_sprite_view_bounds(t_sprite_view *view)
{
	view->start_y = -view->height / 2 + HEIGHT / 2;
	if (view->start_y < 0)
		view->start_y = 0;
	view->end_y = view->height / 2 + HEIGHT / 2;
	if (view->end_y >= HEIGHT)
		view->end_y = HEIGHT - 1;
	view->start_x = -view->width / 2 + view->screen_x;
	if (view->start_x < 0)
		view->start_x = 0;
	view->end_x = view->width / 2 + view->screen_x;
	if (view->end_x >= WIDTH)
		view->end_x = WIDTH - 1;
}

static void	render_sprite_columns(t_game *game, t_sprite *sprite,
	t_sprite_transform *transform, t_sprite_view *view)
{
	int						x;
	t_sprite_render_data	data;

	data.view = view;
	data.transform = transform;
	x = view->start_x;
	while (x < view->end_x)
	{
		draw_sprite_column(game, sprite, x, &data);
		x++;
	}
}

void	render_single_sprite(t_game *game, t_sprite *sprite)
{
	t_sprite_transform	transform;
	t_sprite_view		view;

	calc_sprite_transform(game, sprite, &transform);
	if (transform.transform_y <= 0)
		return ;
	calc_sprite_view_data(&transform, &view);
	calc_sprite_view_bounds(&view);
	render_sprite_columns(game, sprite, &transform, &view);
}
