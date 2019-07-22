/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 19:10:52 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 22:04:32 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void		handle_cam_z(int keycode, t_handle_event *event)
{
	if (keycode == MOVE_FORWARD)
	{
		event->cam_moove.z += 5;
		set_img(event);
	}
	if (keycode == MOVE_BACKWARD)
	{
		event->cam_moove.z -= 5;
		set_img(event);
	}
	if (keycode == ROT_Z_RIGHT)
	{
		event->cam_rot.z += 5;
		event->cam_rot.z = event->cam_rot.z % 360;
		set_img(event);
	}
	if (keycode == ROT_Z_LEFT)
	{
		event->cam_rot.z -= 5;
		event->cam_rot.z = event->cam_rot.z % 360;
		set_img(event);
	}
}

void		handle_cam_moove(int keycode, t_handle_event *event)
{
	if (keycode == MOVE_UP)
	{
		event->cam_moove.y += 5;
		set_img(event);
	}
	if (keycode == MOVE_DOWN)
	{
		event->cam_moove.y -= 5;
		set_img(event);
	}
	if (keycode == MOVE_LEFT)
	{
		event->cam_moove.x -= 5;
		set_img(event);
	}
	if (keycode == MOVE_RIGHT)
	{
		event->cam_moove.x += 5;
		set_img(event);
	}
	if (keycode == MOVE_FORWARD || keycode == MOVE_BACKWARD
			|| keycode == ROT_Z_RIGHT || keycode == ROT_Z_LEFT)
		handle_cam_z(keycode, event);
}

void		handle_cam_rot(int keycode, t_handle_event *event)
{
	if (keycode == UP)
	{
		event->cam_rot.x += 5;
		event->cam_rot.x = event->cam_rot.x % 360;
		set_img(event);
	}
	if (keycode == DOWN)
	{
		event->cam_rot.x -= 5;
		event->cam_rot.x = event->cam_rot.x % 360;
		set_img(event);
	}
	if (keycode == LEFT)
	{
		event->cam_rot.y += 5;
		event->cam_rot.y = event->cam_rot.y % 360;
		set_img(event);
	}
	if (keycode == RIGHT)
	{
		event->cam_rot.y -= 5;
		event->cam_rot.y = event->cam_rot.y % 360;
		set_img(event);
	}
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_handle_event *event;

	x = 0;
	y = 0;
	event = (t_handle_event *)param;
	reset_img(event);
	if (button == ZOOM_IN)
	{
		event->flag = ZOOM_IN;
		event->cam_moove.z += 30;
		set_img(event);
	}
	if (button == ZOOM_OUT)
	{
		event->flag = ZOOM_OUT;
		event->cam_moove.z -= 30;
		set_img(event);
	}
	return (0);
}

int			key_press(int keycode, void *param)
{
	t_handle_event *event;

	event = (t_handle_event *)param;
	reset_img(event);
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		handle_cam_rot(keycode, event);
	if (keycode == MOVE_UP || keycode == MOVE_DOWN
			|| keycode == MOVE_RIGHT || keycode == MOVE_LEFT
			|| keycode == MOVE_FORWARD || keycode == MOVE_BACKWARD
			|| keycode == ROT_Z_RIGHT || keycode == ROT_Z_LEFT)
		handle_cam_moove(keycode, event);
	if (keycode == NEXT_COLOR || keycode == PREV_COLOR)
		handle_color(keycode, event);
	if (keycode == UP_Z || keycode == DOWN_Z)
		smooth_z(event, keycode);
	if (keycode == PERSPCT_PROJ || keycode == ORTHO_PROJ
			|| keycode == ISO_PROJ || keycode == RESET)
		change_proj(event, keycode);
	if (keycode == EXIT)
		exit_window(event, keycode);
	return (0);
}
