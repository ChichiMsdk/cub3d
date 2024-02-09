#include "include/cube.h"
#include <mlx.h>

void	cleaner(t_data *data)
{
	mlx_destroy_image(data->co_id, data->img_ptr);
	mlx_destroy_window(data->co_id, data->win_id);
	mlx_destroy_display(data->co_id);
}

int	key_handler(int keycode, t_data *data)
{
//	printf("%d\n", keycode);
	if (keycode == 0xff1b)
#ifdef Linux
		mlx_loop_end(data->co_id);
#else
	{
		cleaner(data);
		exit(1);
	}
#endif
	else if (keycode == 0x0073) // s
	{
		data->coord->y -= 0.5000;;
		printf("y = %f\n", data->coord->y);
	}
	else if (keycode == 0x0066) // f
	{
		data->coord->y += 0.5000;;
		printf("y = %f\n", data->coord->y);
	}
	else if (keycode == 0x0064) // d
	{
		data->coord->x += 0.5000;;
		printf("x = %f\n", data->coord->x);
	}
	else if (keycode == 0x0065) // e
	{
		data->coord->x -= 0.5000;;
		printf("x = %f\n", data->coord->x);
	}
	else if (keycode == 0xff51) //left
	{
		rotate(data, LEFT);
	}
	else if (keycode == 0xff53) //right
	{
		rotate(data, RIGHT);
	}
	return (keycode);
}

void	free_resources(void *mlx_ptr, void *mlx_window)
{
	mlx_destroy_window(mlx_ptr, mlx_window);
	mlx_destroy_display(mlx_ptr);
}
