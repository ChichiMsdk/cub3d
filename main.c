#include "include/cube.h"
#include <X11/X.h>
#include <X11/keysymdef.h>
#include <mlx.h>

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	*raycaster(t_data *img)
{
	double posX = img->coord->x;
	double posY = img->coord->y;
	double dirX = img->coord->dirX;
	double dirY = img->coord->dirY;
	double planeX = img->coord->planeX;
	double planeY = img->coord->planeY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawEnd >= WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT - 1;
		int color;
		switch (worldMap[mapX][mapY])
		{
			case 1:
				color = 0x00FF0000;
				break;
			case 2:
				color = 0x0000FF00;
				break;
			case 3:
				color = 0x000000FF;
				break;
			case 4:
				color = 0x00FFFF00;
				break;
			case 5:
				color = 0x00FF00FF;
				break;
			default:
				color = 0x00FFFFFF;
				break;
		}
		if (side == 1)
			color = (color >> 1) & 8355711;
		vertical_line(img, x, drawStart, drawEnd, color);
		x++;
	}
	return (img);
}

void	fill_background(t_data *img, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			pixel_to_image(img, x, y, color);
			y++;
		}
		x++;
	}
}

int	loop(t_data *params)
{
	int	i;

	i = 0;
	fill_background(params, 0x00000000);
	raycaster(params);
	mlx_put_image_to_window(params->co_id, params->win_id, params->img_ptr, 0,
		0);
	return (0);
}

int	init_all(t_data *data)
{
	void	*mlx_ptr;
	void	*mlx_window;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		exit(1);
	mlx_window = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cube3D");
	if (!mlx_window)
	{
		mlx_destroy_display(mlx_ptr);
		exit(1);
	}
	data->img_ptr = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr_ptr = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->co_id = mlx_ptr;
	data->win_id = mlx_window;
	if (!data->addr_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		exit(1);
	}

	data->coord->x = 22.000;
	data->coord->y = 12.000;

	data->ctrl->up = 0;
	data->ctrl->down = 0;
	data->ctrl->left = 0;
	data->ctrl->right = 0;
	data->coord->dirX = -1;
	data->coord->dirY = 0;
	data->coord->planeX = 0;
	data->coord->planeY = 0.66;
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_ctrl	ctrl;
	t_coord	coord;

	(void)argc;
	(void)argv;
	data.coord = &coord;
	data.ctrl = &ctrl;
	init_all(&data);
	mlx_hook(data.win_id, 2, 1L << 0, key_handler, &data);
//	mlx_key_hook(data.win_id, key_handler, &data);
	mlx_loop_hook(data.co_id, loop, &data);
	mlx_loop(data.co_id);
	cleaner(&data);
	//free_resources(data.co_id, data.win_id);
	return (0);
}
