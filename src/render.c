#include "cube.h"

void	render_frame(t_game *game)
{
	uint32_t	x;
	t_ray		ray;

	x = 0;
	while (x < game->image->width)
	{
		init_ray(game, x, &ray);
		dda(game, &ray);
		calculate_wall_distance(game, &ray);
		draw_column(game, x, &ray);
		x++;
	}
}
