/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 19:32:58 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 22:05:23 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	smooth_z(t_handle_event *event, int keycode)
{
	if (keycode == UP_Z)
	{
		event->flag = UP_Z;
		event->high += 1;
		set_img(event);
	}
	if (keycode == DOWN_Z)
	{
		event->flag = DOWN_Z;
		event->high -= 1;
		set_img(event);
	}
}

void	exit_window(t_handle_event *event, int keycode)
{
	if (keycode == EXIT)
	{
		event->flag = EXIT;
		mlx_destroy_image(event->mlx_ptr, event->img.img_ptr);
		mlx_destroy_window(event->mlx_ptr, event->win_ptr);
		free_all(event);
		exit(0);
	}
}

void	set_cam_rot(t_handle_event *event, int x, int y, int z)
{
	event->cam_rot.x = x;
	event->cam_rot.y = y;
	event->cam_rot.z = z;
}

void	reset_all(t_handle_event *event, int type)
{
	if (type == 1)
	{
		event->calc = set_mat_y(event->calc, 0);
		event->calc = set_mat_x(event->calc, 0);
		event->calc = set_mat_z(event->calc, 0);
		event->cam_rot.x = 0;
		event->cam_rot.y = 0;
		event->cam_rot.z = 0;
		event->high = 0;
		set_cam_rot(event, 0, 0, 0);
	}
	if (type == 1)
		set_img(event);
}

void	change_proj(t_handle_event *event, int keycode)
{
	if (keycode == RESET)
		reset_all(event, 1);
	if (keycode == PERSPCT_PROJ)
	{
		event->proj = PERSPCT_PROJ;
		reset_all(event, 0);
		set_img(event);
	}
	else if (keycode == ORTHO_PROJ)
	{
		event->proj = ORTHO_PROJ;
		reset_all(event, 0);
		set_img(event);
	}
	else if (keycode == ISO_PROJ)
	{
		event->proj = ORTHO_PROJ;
		reset_all(event, 0);
		set_cam_rot(event, 35, 180, -45);
		set_img(event);
	}
}
