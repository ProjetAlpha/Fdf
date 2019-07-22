/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 19:11:50 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 22:10:35 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	reset_img(t_handle_event *event)
{
	if (event->mlx_ptr && event->img.img_ptr)
	{
		mlx_destroy_image(event->mlx_ptr, event->img.img_ptr);
		event->img.img_ptr = mlx_new_image(event->mlx_ptr,
				WIN_WIDTH, WIN_HEIGHT);
		event->img.bpp = 0;
		event->img.size_l = 0;
		event->img.size_l = 0;
	}
}

void	set_img(t_handle_event *event)
{
	event->img.data = (int *)mlx_get_data_addr(event->img.img_ptr,
			&event->img.bpp, &event->img.size_l,
			&event->img.endian);
	set_points(event);
	mlx_put_image_to_window(event->mlx_ptr,
			event->win_ptr, event->img.img_ptr, 0, 0);
}

void	reset(t_vec3 vec)
{
	vec.x = 0.0;
	vec.y = 0.0;
	vec.z = 0.0;
}

int		dist(int xa, int xb, int ya, int yb)
{
	return (sqrt(pow((xb - xa), 2) + pow((yb - ya), 2)));
}

void	line_parsing_util(t_handle_event *event, t_points *begin, int c_x)
{
	if (c_x > event->map_width)
		event->map_width = c_x;
	event->map->points = begin;
	if (!event->map_width)
		event->map_width = c_x;
	if (!c_x)
	{
		ft_putstr("Map error : unexpected line.");
		free_all(event);
		exit(0);
	}
}
