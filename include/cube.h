# ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <error.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 800
# define PI 3.14159265359
# define RAD 0.0174533

enum
{
	SUCCESS = 0,
	FAILURE = 1,
	CRITICAL_FAILURE = 2,
	MALLOC_FAILURE = 3,
};

enum
{
	LEFT = 8,
	RIGHT = 9,
	BLACK = 0x000000,
	WHITE = 0xffffff,
	GREEN = 0x00ff00,
	BLUE = 0x0000ff,
	YELLOW = 0xffff00,
	PURPLE = 0x800080,
	ORANGE = 0xffa500,
	RED = 0xff0000,
};

typedef struct trashcan
{
	int				dx;
	int				dy;
	int				x;
	int				y;
	int				x_end;
	int				y_end;
	int				p;
	int				x_increment;
	int				y_increment;

}					t_trashcan;

typedef	struct t_coord
{
	double x;
	double y;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
}t_coord;

typedef	struct t_point
{
	int x;
	int y;
}				t_point;

typedef struct ctrl
{
	int		up;
	int		down;
	int		left;
	int		right;
}t_ctrl;

typedef struct t_data 
{
	void			*img_ptr;
	char			*addr_ptr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*co_id;
	void			*win_id;
	t_ctrl			*ctrl;
	t_coord			*coord;
}					t_data;

void	liner(t_data *img, t_point x1, t_point x2, int color);
void	draw_line(t_data *img, t_point p1, t_point p2, int color);
int		key_handler(int keycode, t_data *data);
void	free_resources(void *mlx_ptr, void *mlx_window);
void	pixel_to_image(t_data *img, int x, int y, int color);
void	cleaner(t_data *data);
void	vertical_line(t_data *img, int x, int drawStart, int drawEnd, int color);
void	rotate(t_data *params, int DIRECTION);

#endif
