#include "cube.h"
/*
	Принимает смещение относительно центра мини-карты (offset от -MINIMAP_RADIUS до +MINIMAP_RADIUS)
	Возвращает координату на экране в пикселях
*/
int	get_screen_pos(int offset)
{
	return (MINIMAP_OFFSET + (offset + MINIMAP_RADIUS) * MINIMAP_TILE_SIZE);
}
