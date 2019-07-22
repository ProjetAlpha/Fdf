/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_struct.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 23:18:30 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 21:27:31 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

t_img			init_img(void)
{
	t_img img;

	img.img_ptr = NULL;
	img.data = 0;
	img.bpp = 0;
	img.size_l = 0;
	img.endian = 0;
	return (img);
}

t_points		*init_points(void)
{
	t_points *pnt;

	pnt = malloc(sizeof(t_points));
	pnt->next = NULL;
	pnt->vec = init_vec();
	pnt->is_end = 0;
	return (pnt);
}

t_map			*init_map(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	map->next = NULL;
	map->line_width = 0;
	map->points = init_points();
	return (map);
}

void			init_dim(t_handle_event *event)
{
	event->map_height = 0;
	event->map_width = 0;
	event->win_height = 0;
	event->win_width = 0;
	event->max_depth = 0;
	event->min_x = INT_MAX;
	event->max_x = 0;
	event->min_y = INT_MAX;
	event->max_y = 0;
	event->high = 0;
	event->min_depth = INT_MAX;
}

t_handle_event	*init_event(void)
{
	t_handle_event *event;

	event = malloc(sizeof(t_handle_event));
	event->mlx_ptr = NULL;
	event->win_ptr = NULL;
	init_dim(event);
	event->proj = 0;
	event->img = init_img();
	event->map = init_map();
	event->flag = 0;
	event->zoom = 0;
	event->proj = ORTHO_PROJ;
	event->color_rank = 0;
	event->cam_moove = init_moove();
	event->cam_rot = init_rot();
	event->calc = init_calc();
	return (event);
}
