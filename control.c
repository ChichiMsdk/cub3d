#include "include/cube.h"

void	rotate(t_data *params, int DIRECTION)
{
	if (DIRECTION == LEFT)
	{
		printf("LEFT\n");
      	double oldDirX = params->coord->dirX;
      	params->coord->dirX = params->coord->dirX * cos(RAD) - 
			params->coord->dirY * sin(RAD);
      	params->coord->dirY = oldDirX * sin(RAD) + params->coord->dirY * cos(RAD);
      	double oldPlaneX = params->coord->planeX;
      	params->coord->planeX = params->coord->planeX * cos(RAD) -
			params->coord->planeY * sin(RAD);
      	params->coord->planeY = oldPlaneX * sin(RAD) + params->coord->planeY * 
			cos(RAD);
	}
	if (DIRECTION == RIGHT)
	{
		printf("RIGHT\n");
      	double oldDirX = params->coord->dirX;
      	params->coord->dirX = params->coord->dirX * cos(-RAD) - 
			params->coord->dirY * sin(-RAD);
      	params->coord->dirY = oldDirX * sin(-RAD) + params->coord->dirY * cos(-RAD);
      	double oldPlaneX = params->coord->planeX;
      	params->coord->planeX = params->coord->planeX * cos(-RAD) -
			params->coord->planeY * sin(-RAD);
      	params->coord->planeY = oldPlaneX * sin(-RAD) + params->coord->planeY * 
			cos(-RAD);
	}
}
