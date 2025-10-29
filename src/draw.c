#include "cube.h"

int	load_textures(t_textures *textures, t_config *config)
{
1. Загрузить текстуру North из config->north
       Если ошибка → вывести сообщение, вернуть 0
	   mlx_load_png(config->north)
	   mlx_delete_texture
	   mlx_texture_to_image   >mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);
}
