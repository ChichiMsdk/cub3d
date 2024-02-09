#include "include/cube.h"

void	pixel_to_image(t_data *img, int x, int y, int color)
{
	char	*pixel;

	if (y <= 0 || y >= WINDOW_HEIGHT)
		return ;
	if (x <= 0 || x >= WINDOW_WIDTH)
		return ;
	pixel = img->addr_ptr + (y * img->line_length + x * (img->bits_per_pixel
				/ 8));
	*(unsigned int *)pixel = color;
}

void	setting_trashcan(t_trashcan *trash, t_point x1, t_point x2)
{
	trash->dx = x2.x - x1.x;
	trash->dy = x2.y - x1.y;
	trash->x_increment = 1;
	trash->y_increment = 1;
	if (trash->dx < 0)
		trash->x_increment = -1;
	if (trash->dy < 0)
		trash->y_increment = -1;
	trash->dx = abs(trash->dx);
	trash->dy = abs(trash->dy);
	trash->x = x1.x;
	trash->y = x1.y;
}

void	liner_part2( t_trashcan *trash, t_data *img, int color)
{
	if (trash->x_increment == -1)
	{
		while (trash->x > trash->x_end)
		{
			trash->x += trash->x_increment;
			if (trash->p < 0)
				trash->p += 2 * trash->dy;
			else
			{
				trash->y += trash->y_increment;
				trash->p += 2 * (trash->dy - trash->dx);
			}
			pixel_to_image(img, trash->x, trash->y, color);
		}
	}
}

void	liner_part3( t_trashcan *t, t_data *img, int color)
{
	if (t->x_increment == 1)
	{
		while (t->x < t->x_end)
		{
			t->x += t->x_increment;
			if (t->p < 0)
			{
				t->p += 2 * t->dy;
			}
			else
			{
				t->y += t->y_increment;
				t->p += 2 * (t->dy - t->dx);
			}
			pixel_to_image(img, t->x, t->y, color);
		}
	}
}

void	liner_part4( t_trashcan *t, t_data *img, int color)
{
	if (t->y_increment == -1)
	{
		while (t->y > t->x_end)
		{
			t->y += t->y_increment;
			if (t->p < 0)
			{
				t->p += 2 * t->dx;
			}
			else
			{
				t->x += t->x_increment;
				t->p += 2 * (t->dx - t->dy);
			}
			pixel_to_image(img, t->x, t->y, color);
		}
	}
}

void	liner_part5( t_trashcan *t, t_data *img, int color)
{
	if (t->y_increment == 1)
	{
		while (t->y < t->x_end)
		{
			t->y += t->y_increment;
			if (t->p < 0)
			{
				t->p += 2 * t->dx;
			}
			else
			{
				t->x += t->x_increment;
				t->p += 2 * (t->dx - t->dy);
			}
			pixel_to_image(img, t->x, t->y, color);
		}
	}
}

void	liner(t_data *img, t_point x1, t_point x2, int color)
{
	t_trashcan	trash;

	setting_trashcan(&trash, x1, x2);
	if (trash.dx > trash.dy)
	{
		trash.p = 2 * trash.dy - trash.dx;
		trash.x_end = x2.x;
		liner_part2(&trash, img, color);
		liner_part3(&trash, img, color);
	}
	else
	{
		trash.p = 2 * trash.dx - trash.dy;
		trash.x_end = x2.y;
		liner_part4(&trash, img, color);
		liner_part5(&trash, img, color);
	}
}
