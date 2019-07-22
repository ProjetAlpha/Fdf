/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   color.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/06 17:20:18 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 21:20:12 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

int		create_rgba(int r, int g, int b, int a)
{
	return ((a & 0xff) + ((r & 0xff) << 24) +
			((g & 0xff) << 16) + ((b & 0xff) << 8));
}

int		lerp(int a, int b, double ratio)
{
	int mask1;
	int mask2;
	int f2;
	int f1;

	mask1 = 0x00ff00ff;
	mask2 = 0xff00ff00;
	f2 = (int)(256 * ratio);
	f1 = 256 - f2;
	return (((((a & mask1) * f1) + ((b & mask1) * f2)) >> 8) & mask1)
	| (((((a & mask2) * f1) + ((b & mask2) * f2)) >> 8) & mask2);
}

void	handle_color(int keycode, t_handle_event *event)
{
	if (keycode == NEXT_COLOR)
	{
		event->flag = NEXT_COLOR;
		event->color_rank++;
		if (event->color_rank > 4)
			event->color_rank = 0;
		set_img(event);
	}
	if (keycode == PREV_COLOR)
	{
		event->flag = PREV_COLOR;
		event->color_rank--;
		if (event->color_rank < 0)
			event->color_rank = 4;
		set_img(event);
	}
}

int		get_color(int index, int type)
{
	const static int dark_color[] = {0x8e8e90, 0x49494b,
		0x91684a, 0x00303f, 0x7A9D96};
	const static int light_color[] = {0xf6f5f3,
		0x7dce94, 0xcd5554, 0x313d4b, 0x00c07f};

	if (type == 1)
		return (dark_color[index]);
	if (type == 2)
		return (light_color[index]);
	return (0);
}

int		choose_color(double curr_z, double next_z)
{
	if (curr_z == 0.0 && next_z == 0.0)
		return (0xffffff);
	if (curr_z == next_z)
		return (0x41d6f4);
	return (-1);
}
