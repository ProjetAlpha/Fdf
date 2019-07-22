/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_ortho_matrix.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 17:38:40 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 22:00:48 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

t_calc		reset_proj_matrix(t_calc calc)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			calc.mat_proj[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (calc);
}

t_vec3		create_vec(int x, int y, int z)
{
	t_vec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_calc		set_values(t_calc calc, float max, float f, float n)
{
	float r;
	float b;
	float l;
	float t;

	r = max * WIN_WIDTH / WIN_HEIGHT;
	l = -r;
	t = max;
	b = -t;
	calc.mat_proj[0][0] = 2 / (r - l);
	calc.mat_proj[1][1] = 2 / (t - b);
	calc.mat_proj[2][2] = -2 / (f - n);
	calc.mat_proj[3][0] = -(r + l) / (r - l);
	calc.mat_proj[3][1] = -(t + b) / (t - b);
	calc.mat_proj[3][2] = -(f + n) / (f - n);
	calc.mat_proj[3][3] = 1;
	return (calc);
}

t_calc		set_ortho_matrix(t_handle_event *event, float far, float near)
{
	t_vec3	min_camera;
	t_vec3	max_camera;
	float	max;

	event->calc = reset_proj_matrix(event->calc);
	min_camera = mult_cam(event->calc,
			create_vec(event->min_x, event->min_y, event->min_depth));
	max_camera = mult_cam(event->calc,
			create_vec(event->max_x, event->max_y, event->max_depth));
	max = MAX(MAX(fabs(min_camera.x),
				fabs(max_camera.x)), MAX(fabs(min_camera.y),
				fabs(max_camera.y))) + event->cam_moove.z;
	return (set_values(event->calc, max, far, near));
}
