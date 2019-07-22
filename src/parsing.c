/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 22:16:10 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 21:58:52 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void				set_min_max(t_handle_event *event,
		int x, int y, int z)
{
	if (x > event->max_x)
		event->max_x = (int)event->map->points->vec.x;
	if (x < event->min_x)
		event->min_x = (int)event->map->points->vec.x;
	if (y > event->max_y)
		event->max_y = (int)event->map->points->vec.y;
	if (y < event->min_y)
		event->min_y = (int)event->map->points->vec.y;
	if (z > event->max_depth)
		event->max_depth = (int)event->map->points->vec.z;
	if (z < event->min_depth)
		event->min_depth = (int)event->map->points->vec.z;
}

void				store_pnts(t_points *begin, t_handle_event *event,
		char *tmp, int is_end)
{
	if (is_end)
	{
		event->map->points->is_end = 1;
		event->map->points->vec.z = (double)ft_atoi(tmp);
		set_min_max(event, (int)event->map->points->vec.x,
				(int)event->map->points->vec.y, (int)event->map->points->vec.z);
		event->map->points = begin;
		return ;
	}
	event->map->points->vec.z = (double)ft_atoi(tmp);
	set_min_max(event, (int)event->map->points->vec.x,
			(int)event->map->points->vec.y, (int)event->map->points->vec.z);
	event->map->points->next = init_points();
	event->map->points = event->map->points->next;
}

int					get_z(char *line, t_handle_event *event, t_points *begin)
{
	int		is_neg;
	int		c_digit;
	char	*tmp;

	tmp = NULL;
	is_neg = 0;
	c_digit = 0;
	(*line == '-') ? is_neg++ : 0;
	c_digit = (is_neg == 1) ? 1 : 0;
	while (ft_isdigit(line[c_digit]) && line[c_digit])
		c_digit++;
	if ((c_digit > 0 && is_neg == 0) || (c_digit > 1 && is_neg == 1))
		tmp = ft_strsub(line, 0, c_digit);
	if (*line && tmp != NULL)
	{
		if (is_end(line))
		{
			store_pnts(begin, event, tmp, 1);
			free(tmp);
			return (-1);
		}
		store_pnts(begin, event, tmp, 0);
		free(tmp);
	}
	return (0);
}

void				store_vec(char *line, t_handle_event *event, int y)
{
	int			c_x;
	t_points	*begin;

	c_x = 0;
	begin = event->map->points;
	while (*line)
	{
		while (((!ft_isdigit(*line) &&
						!(*line == '-' && ft_isdigit(*(line + 1))))
					|| (*line == '0' && *(line + 1) == 'x')) && *line)
			line++;
		if (ft_isdigit(*line) || (ft_isdigit(*(line + 1)) && *line == '-'))
		{
			event->map->points->vec.x = (double)c_x;
			event->map->points->vec.y = (double)y;
			c_x++;
		}
		if (get_z(line, event, begin) == -1)
			break ;
		while ((ft_isdigit(*line) || *line == '-'
					|| (*line == '0' && *(line + 1) == 'x')) && *line)
			line++;
		line++;
	}
	line_parsing_util(event, begin, c_x);
}

t_handle_event		*read_file(t_handle_event *event, char *map)
{
	char	*line;
	int		fd;
	int		c_y;
	t_map	*begin;

	c_y = 0;
	begin = event->map;
	fd = open(map, O_RDWR);
	if (fd < 0)
	{
		free_all(event);
		exit(0);
	}
	while (get_next_line(fd, &line) > 0)
	{
		store_vec(line, event, c_y);
		event->map->next = init_map();
		event->map = event->map->next;
		free(line);
		c_y++;
	}
	event->map = begin;
	event->map_height = c_y;
	close(fd);
	return (event);
}
