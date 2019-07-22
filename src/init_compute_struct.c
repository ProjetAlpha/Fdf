/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_calc_struct.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 18:58:44 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 21:40:39 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

t_calc		init_calc(void)
{
	t_calc	calc;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			calc.mat_proj[i][j] = 0.0;
			calc.world_cam[i][j] = 0.0;
			calc.y_rotation[i][j] = 0.0;
			calc.x_rotation[i][j] = 0.0;
			calc.z_rotation[i][j] = 0.0;
			calc.ortho_mat[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (calc);
}

t_vec3		init_vec(void)
{
	t_vec3 vec;

	vec.x = 0.0;
	vec.y = 0.0;
	vec.z = 0.0;
	return (vec);
}

t_rotate	init_rot(void)
{
	t_rotate rot;

	rot.x = 0;
	rot.y = 0;
	rot.z = 0;
	return (rot);
}

t_moove		init_moove(void)
{
	t_moove moove;

	moove.x = 0;
	moove.y = 0;
	moove.z = 0;
	return (moove);
}
