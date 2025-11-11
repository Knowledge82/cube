#include "cube.h"

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(angle);
	sin_rot = sin(angle);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_rot
		- game->player.dir_y * sin_rot;
	game->player.dir_y = old_dir_x * sin_rot
		+ game->player.dir_y * cos_rot;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos_rot
		- game->player.plane_y * sin_rot;
	game->player.plane_y = old_plane_x * sin_rot
		+ game->player.plane_y * cos_rot;
}

void	handle_rotation(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, game->rotation_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, -1 * game->rotation_speed);
}
