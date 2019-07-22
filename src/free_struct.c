/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_struct.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 22:37:19 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 21:15:57 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	free_all(t_handle_event *event)
{
	t_map		*next_line;
	t_points	*next_pnt;
	t_points	*head;

	while (event->map)
	{
		head = event->map->points;
		while (head)
		{
			next_pnt = head->next;
			free(head);
			head = next_pnt;
		}
		next_line = event->map->next;
		free(event->map);
		event->map = next_line;
	}
	free(event->mlx_ptr);
	free(event);
}

void	free_pnts(t_points *points)
{
	t_points *next;

	while (points)
	{
		next = points->next;
		free(points);
		points = next;
	}
}
