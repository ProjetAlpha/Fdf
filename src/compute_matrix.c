/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calc.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 18:54:15 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 22:00:12 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	mult_matrix(t_calc calc, t_vec3 curr_vec3, int type)
{
	t_vec3	vec;

	if (type == PROJ)
		vec = mult_proj(calc, curr_vec3);
	if (type == CAM)
		vec = mult_cam(calc, curr_vec3);
	if (type == ROT_Y)
		vec = mult_rot_y(calc, curr_vec3);
	if (type == ROT_X)
		vec = mult_rot_x(calc, curr_vec3);
	if (type == ROT_Z)
		vec = mult_rot_z(calc, curr_vec3);
	return (vec);
}
