/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/09 17:52:44 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 18:48:37 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

int				is_end(char *line)
{
	while ((ft_isdigit(*line) || *line == '-') && *line)
		line++;
	while (((!ft_isdigit(*line) && !(*line == '-' && ft_isdigit(*(line + 1))))
				|| (*line == '0' && *(line + 1) == 'x')) && *line)
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

int				is_outside(int x, int y)
{
	return ((x == 0 || y == 0)
			|| (x < 0 || x > WIN_WIDTH) || (y < 0 || y > WIN_HEIGHT));
}

t_vec3			get_next_vec(t_map *line, t_vec3 curr_vec)
{
	t_points *pnts;

	pnts = line->points;
	while (pnts)
	{
		if (pnts->vec.y == curr_vec.y + 1 && pnts->vec.x == curr_vec.x)
			return (pnts->vec);
		pnts = pnts->next;
	}
	return (curr_vec);
}

t_vec3			calc_rot(t_handle_event *event, t_vec3 src)
{
	t_vec3 vec;

	if (event->cam_rot.x != 0)
		vec = mult_matrix(event->calc, src, ROT_X);
	if (event->cam_rot.y != 0)
	{
		if (event->cam_rot.x != 0)
			vec = mult_matrix(event->calc, vec, ROT_Y);
		else
			vec = mult_matrix(event->calc, src, ROT_Y);
	}
	if (event->cam_rot.z != 0)
	{
		if (event->cam_rot.y != 0 || event->cam_rot.x != 0)
			vec = mult_matrix(event->calc, vec, ROT_Z);
		else
			vec = mult_matrix(event->calc, src, ROT_Z);
	}
	return (vec);
}

int				is_rot(t_handle_event *event)
{
	if (event->cam_rot.x != 0 || event->cam_rot.y != 0 || event->cam_rot.z != 0)
		return (1);
	return (0);
}
