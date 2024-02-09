#include "include/cube.h"

void	vertical_line(t_data *img, int x, int drawStart, int drawEnd, int color)
{
	int	y;

	y = drawStart;
	while (y < drawEnd)
	{
		pixel_to_image(img, x, y, color);
		y++;
	}
}
