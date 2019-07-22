/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 23:37:25 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 18:41:13 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

t_line	set_first_line(t_line line, t_vec3 new_vec)
{
	line.p1.x = (int)((new_vec.x + 1.0) * 0.5 * WIN_WIDTH);
	line.p1.y = (int)(((1.0 - (new_vec.y + 1.0) * 0.5) * WIN_HEIGHT));
	return (line);
}

t_line	set_second_line(t_line line, t_vec3 sec_vec)
{
	line.p2.x = (int)((sec_vec.x + 1.0) * 0.5 * WIN_WIDTH);
	line.p2.y = (int)(((1.0 - (sec_vec.y + 1.0) * 0.5) * WIN_HEIGHT));
	return (line);
}

t_line	set_horizontal_pnt(t_line line,
		t_handle_event *event, t_points *pnt_head, t_vec3 curr_vec)
{
	t_vec3	sec_vec;
	t_vec3	new_vec;
	int		tmp;

	new_vec = mult_matrix(event->calc, mult_matrix(event->calc, is_rot(event) ?
				calc_rot(event, curr_vec) : curr_vec, CAM), PROJ);
	line = set_first_line(line, new_vec);
	if (pnt_head->next != NULL && !pnt_head->is_end)
	{
		sec_vec = pnt_head->next->vec;
		if (sec_vec.z != 0.0)
			sec_vec.z += event->high;
		tmp = sec_vec.z;
		sec_vec = mult_matrix(event->calc, mult_matrix(event->calc,
					is_rot(event) ? calc_rot(event, sec_vec)
					: sec_vec, CAM), PROJ);
		line = set_second_line(line, sec_vec);
		line.curr_z = tmp;
		if (!is_outside(line.p1.x, line.p1.y)
				&& !is_outside(line.p2.x, line.p2.y))
			draw_line(event, line, choose_color(curr_vec.z, tmp));
		line.p2.x = 0;
		line.p2.y = 0;
	}
	return (line);
}

t_line	set_vertical_pnt(t_line line,
		t_handle_event *event, t_points *pnt_head, t_vec3 curr_vec)
{
	t_vec3	next_vec;
	t_vec3	new_vec;

	if (event->map->next)
		next_vec = get_next_vec(event->map->next, pnt_head->vec);
	if (next_vec.y != pnt_head->vec.y
			&& event->map->next && next_vec.y != event->map_height)
	{
		if (next_vec.z != 0.0)
			next_vec.z += event->high;
		new_vec = mult_matrix(event->calc, mult_matrix(event->calc,
					is_rot(event) ? calc_rot(event, next_vec) :
					next_vec, CAM), PROJ);
		line = set_second_line(line, new_vec);
		line.curr_z = next_vec.z;
		if (!is_outside(line.p1.x, line.p1.y)
				&& !is_outside(line.p2.x, line.p2.y))
			draw_line(event, line, choose_color(curr_vec.z, next_vec.z));
		line.p2.x = 0;
		line.p2.y = 0;
	}
	return (line);
}
