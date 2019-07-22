/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mult_matrix.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 18:50:41 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 21:40:24 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

t_vec3		mult_proj(t_calc calc, t_vec3 curr_vec3)
{
	t_vec3 vec;

	vec.x = (curr_vec3.x * calc.mat_proj[0][0]) +
		(curr_vec3.y * calc.mat_proj[1][0]) +
		(curr_vec3.z * calc.mat_proj[2][0]) + calc.mat_proj[3][0];
	vec.y = (curr_vec3.x * calc.mat_proj[0][1]) +
		(curr_vec3.y * calc.mat_proj[1][1]) +
		(curr_vec3.z * calc.mat_proj[2][1]) + calc.mat_proj[3][1];
	vec.z = (curr_vec3.x * calc.mat_proj[0][2]) +
		(curr_vec3.y * calc.mat_proj[1][2]) +
		(curr_vec3.z * calc.mat_proj[2][2]) + calc.mat_proj[3][2];
	vec.w = (curr_vec3.x * calc.mat_proj[0][3]) +
		(curr_vec3.y * calc.mat_proj[1][3]) +
		(curr_vec3.z * calc.mat_proj[2][3]) + calc.mat_proj[3][3];
	if (vec.w != 0.0 && vec.w != 1)
	{
		vec.x = vec.x / vec.w;
		vec.y = vec.y / vec.w;
		vec.z = vec.z / vec.w;
	}
	return (vec);
}

t_vec3		mult_cam(t_calc calc, t_vec3 curr_vec3)
{
	t_vec3 vec;

	vec.x = (curr_vec3.x * calc.world_cam[0][0]) +
		(curr_vec3.y * calc.world_cam[1][0]) +
		(curr_vec3.z * calc.world_cam[2][0]) + calc.world_cam[3][0];
	vec.y = (curr_vec3.x * calc.world_cam[0][1]) +
		(curr_vec3.y * calc.world_cam[1][1]) +
		(curr_vec3.z * calc.world_cam[2][1]) + calc.world_cam[3][1];
	vec.z = (curr_vec3.x * calc.world_cam[0][2]) +
		(curr_vec3.y * calc.world_cam[1][2]) +
		(curr_vec3.z * calc.world_cam[2][2]) + calc.world_cam[3][2];
	vec.w = (curr_vec3.x * calc.world_cam[0][3]) +
		(curr_vec3.y * calc.world_cam[1][3]) +
		(curr_vec3.z * calc.world_cam[2][3]) + calc.world_cam[3][3];
	if (vec.w != 0.0 && vec.w != 1)
	{
		vec.x = vec.x / vec.w;
		vec.y = vec.y / vec.w;
		vec.z = vec.z / vec.w;
	}
	return (vec);
}

t_vec3		mult_rot_y(t_calc calc, t_vec3 curr_vec3)
{
	t_vec3 vec;

	vec.x = (curr_vec3.x * calc.y_rotation[0][0]) +
		(curr_vec3.y * calc.y_rotation[1][0]) +
		(curr_vec3.z * calc.y_rotation[2][0]) + calc.y_rotation[3][0];
	vec.y = (curr_vec3.x * calc.y_rotation[0][1]) +
		(curr_vec3.y * calc.y_rotation[1][1]) +
		(curr_vec3.z * calc.y_rotation[2][1]) + calc.y_rotation[3][1];
	vec.z = (curr_vec3.x * calc.y_rotation[0][2]) +
		(curr_vec3.y * calc.y_rotation[1][2]) +
		(curr_vec3.z * calc.y_rotation[2][2]) + calc.y_rotation[3][2];
	vec.w = (curr_vec3.x * calc.y_rotation[0][3]) +
		(curr_vec3.y * calc.y_rotation[1][3]) +
		(curr_vec3.z * calc.y_rotation[2][3]) + calc.y_rotation[3][3];
	if (vec.w != 0.0 && vec.w != 1)
	{
		vec.x = vec.x / vec.w;
		vec.y = vec.y / vec.w;
		vec.z = vec.z / vec.w;
	}
	return (vec);
}

t_vec3		mult_rot_x(t_calc calc, t_vec3 curr_vec3)
{
	t_vec3 vec;

	vec.x = (curr_vec3.x * calc.x_rotation[0][0]) +
		(curr_vec3.y * calc.x_rotation[1][0]) +
		(curr_vec3.z * calc.x_rotation[2][0]) + calc.x_rotation[3][0];
	vec.y = (curr_vec3.x * calc.x_rotation[0][1]) +
		(curr_vec3.y * calc.x_rotation[1][1]) +
		(curr_vec3.z * calc.x_rotation[2][1]) + calc.x_rotation[3][1];
	vec.z = (curr_vec3.x * calc.x_rotation[0][2]) +
		(curr_vec3.y * calc.x_rotation[1][2]) +
		(curr_vec3.z * calc.x_rotation[2][2]) + calc.x_rotation[3][2];
	vec.w = (curr_vec3.x * calc.x_rotation[0][3]) +
		(curr_vec3.y * calc.x_rotation[1][3]) +
		(curr_vec3.z * calc.x_rotation[2][3]) + calc.x_rotation[3][3];
	if (vec.w != 0.0 && vec.w != 1)
	{
		vec.x = vec.x / vec.w;
		vec.y = vec.y / vec.w;
		vec.z = vec.z / vec.w;
	}
	return (vec);
}

t_vec3		mult_rot_z(t_calc calc, t_vec3 curr_vec3)
{
	t_vec3 vec;

	vec.x = (curr_vec3.x * calc.z_rotation[0][0]) +
		(curr_vec3.y * calc.z_rotation[1][0]) +
		(curr_vec3.z * calc.z_rotation[2][0]) + calc.z_rotation[3][0];
	vec.y = (curr_vec3.x * calc.z_rotation[0][1]) +
		(curr_vec3.y * calc.z_rotation[1][1]) +
		(curr_vec3.z * calc.z_rotation[2][1]) + calc.z_rotation[3][1];
	vec.z = (curr_vec3.x * calc.z_rotation[0][2]) +
		(curr_vec3.y * calc.z_rotation[1][2]) +
		(curr_vec3.z * calc.z_rotation[2][2]) + calc.z_rotation[3][2];
	vec.w = (curr_vec3.x * calc.z_rotation[0][3]) +
		(curr_vec3.y * calc.z_rotation[1][3]) +
		(curr_vec3.z * calc.z_rotation[2][3]) + calc.z_rotation[3][3];
	if (vec.w != 0.0 && vec.w != 1)
	{
		vec.x = vec.x / vec.w;
		vec.y = vec.y / vec.w;
		vec.z = vec.z / vec.w;
	}
	return (vec);
}
