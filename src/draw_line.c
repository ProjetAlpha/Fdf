/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_line.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 19:50:01 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 22:34:26 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	y_longer(t_handle_event *event, t_line line, int long_len, int color)
{
	int		i;
	int		x;
	int		y;
	int		dst;
	double	diff;

	i = 0;
	dst = dist(line.p1.x, line.p2.x, line.p1.y, line.p2.y);
	diff = fabs((double)line.curr_z / (double)event->max_depth);
	while (i != long_len)
	{
		x = (line.p1.x + (int)((double)i * line.mult_diff));
		y = (line.p1.y + i);
		if (y >= 0 && x >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
			event->img.data[y * WIN_WIDTH + x] =
					(color == -1) ? lerp(line.color2,
					line.color1,
					(double)(((double)abs(i) / (double)abs(dst)) * diff))
					: color;
		i += line.inc_value;
	}
}

void	y_smaller(t_handle_event *event, t_line line, int long_len, int color)
{
	int		i;
	int		x;
	int		y;
	int		dst;
	double	diff;

	i = 0;
	dst = dist(line.p1.x, line.p2.x, line.p1.y, line.p2.y);
	diff = fabs((double)line.curr_z / (double)event->max_depth);
	while (i != long_len)
	{
		x = (line.p1.x + i);
		y = (line.p1.y + (int)((double)i * line.mult_diff));
		if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
			event->img.data[y * WIN_WIDTH + x] =
					(color == -1) ? lerp(line.color1,
					line.color2,
					(double)(((double)abs(i) / (double)abs(dst)) * diff))
					: color;
		i += line.inc_value;
	}
}

void	draw_line(t_handle_event *event, t_line line, int color)
{
	int short_len;
	int tmp;
	int long_len;

	short_len = line.p2.y - line.p1.y;
	long_len = line.p2.x - line.p1.x;
	line.y_longer = 0;
	line.mult_diff = 0;
	line.inc_value = 0;
	if (abs(short_len) > abs(long_len))
	{
		tmp = short_len;
		short_len = long_len;
		long_len = tmp;
		line.y_longer = 1;
	}
	line.inc_value = (long_len < 0) ? -1 : 1;
	line.mult_diff = (long_len == 0) ? (double)short_len :
		(double)short_len / (double)long_len;
	if (line.y_longer == 1)
		y_longer(event, line, long_len, color);
	else
		y_smaller(event, line, long_len, color);
}
