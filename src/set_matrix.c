/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_matrix.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 18:53:58 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 21:46:23 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

t_calc		set_mat_y(t_calc calc, double angle)
{
	double rad;
	double c;
	double s;

	rad = angle * PI / 180;
	c = cos(rad);
	s = sin(rad);
	calc.y_rotation[0][0] = c;
	calc.y_rotation[0][2] = -s;
	calc.y_rotation[1][1] = 1;
	calc.y_rotation[2][0] = s;
	calc.y_rotation[2][2] = c;
	calc.y_rotation[3][3] = 1;
	return (calc);
}

t_calc		set_mat_x(t_calc calc, double angle)
{
	double rad;
	double c;
	double s;

	rad = angle * PI / 180;
	c = cos(rad);
	s = sin(rad);
	calc.x_rotation[0][0] = 1;
	calc.x_rotation[1][1] = c;
	calc.x_rotation[1][2] = s;
	calc.x_rotation[2][1] = -s;
	calc.x_rotation[2][2] = c;
	calc.x_rotation[3][3] = 1;
	return (calc);
}

t_calc		set_mat_z(t_calc calc, double angle)
{
	double rad;
	double c;
	double s;

	rad = angle * PI / 180;
	c = cos(rad);
	s = sin(rad);
	calc.z_rotation[0][0] = c;
	calc.z_rotation[0][1] = s;
	calc.z_rotation[1][0] = -s;
	calc.z_rotation[1][1] = c;
	calc.z_rotation[2][2] = 1;
	calc.z_rotation[3][3] = 1;
	return (calc);
}

t_calc		set_perpective_mat(t_calc calc,
		double fov, double znear, double zfar)
{
	calc = reset_proj_matrix(calc);
	calc.mat_proj[0][0] = 1.0 / tan(fov * 0.5 * M_PI / 180);
	calc.mat_proj[1][1] = 1.0 / tan(fov * 0.5 * M_PI / 180);
	calc.mat_proj[2][2] = -zfar / (zfar - znear);
	calc.mat_proj[2][3] = -1;
	calc.mat_proj[3][2] = -zfar * znear / (zfar - znear);
	return (calc);
}

t_calc		set_camera(t_handle_event *event, t_calc calc,
		int n_elem, int scale)
{
	calc.world_cam[0][0] = 1.0;
	calc.world_cam[1][1] = 1.0;
	calc.world_cam[2][2] = 1.0;
	calc.world_cam[3][0] = -n_elem * 1 / scale + event->cam_moove.x;
	calc.world_cam[3][1] = -n_elem * 1 / scale + event->cam_moove.y;
	calc.world_cam[3][2] = -n_elem * scale / 6 + event->cam_moove.z;
	calc.world_cam[3][3] = 1.0;
	return (calc);
}
