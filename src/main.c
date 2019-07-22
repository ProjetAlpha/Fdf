/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 21:55:05 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 18:47:04 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

t_calc	set_all_calc(t_handle_event *event)
{
	int	n_elem;
	int	scale;

	n_elem = event->map_width > event->map_height
		? event->map_width : event->map_height;
	scale = (event->win_width / 2) / n_elem;
	event->calc = set_camera(event, event->calc, n_elem, scale);
	event->calc = set_mat_y(event->calc, event->cam_rot.y);
	event->calc = set_mat_x(event->calc, event->cam_rot.x);
	event->calc = set_mat_z(event->calc, event->cam_rot.z);
	event->calc = (event->proj == ORTHO_PROJ) ?
		set_ortho_matrix(event, 1000.0, 0.1) :
		set_perpective_mat(event->calc, 90, 0.1, 1000.0);
	return (event->calc);
}

void	set_points(t_handle_event *event)
{
	t_map		*start;
	t_points	*pnt_head;
	t_line		line;
	t_vec3		curr_vec;

	line.color1 = 0x42f486;
	line.color2 = 0xf4bc42;
	line.color3 = 0x2cb72e;
	set_all_calc(event);
	start = event->map;
	while (event->map)
	{
		pnt_head = event->map->points;
		while (pnt_head)
		{
			curr_vec = pnt_head->vec;
			if (pnt_head->vec.z != 0.0 && event->high != 0)
				curr_vec.z += event->high;
			line = set_horizontal_pnt(line, event, pnt_head, curr_vec);
			line = set_vertical_pnt(line, event, pnt_head, curr_vec);
			pnt_head = pnt_head->next;
		}
		event->map = event->map->next;
	}
	event->map = start;
}

void	set_window(t_handle_event *event)
{
	event->mlx_ptr = mlx_init();
	event->win_ptr = mlx_new_window(event->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "mlx 42");
	if (!event->win_ptr)
	{
		ft_putstr("error : mlx failed to create a window.\n");
		exit(0);
	}
	event->win_height = WIN_HEIGHT;
	event->win_width = WIN_WIDTH;
	event->img.img_ptr = mlx_new_image(event->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	event->img.data = (int *)mlx_get_data_addr(event->img.img_ptr,
			&event->img.bpp, &event->img.size_l, &event->img.endian);
	set_points(event);
	mlx_put_image_to_window(event->mlx_ptr,
			event->win_ptr, event->img.img_ptr, 0, 0);
	mlx_hook(event->win_ptr, 2, 1L << 0, key_press, (void*)event);
	mlx_hook(event->win_ptr, 4, 1L << 0, mouse_press, (void*)event);
	mlx_loop(event->mlx_ptr);
	mlx_destroy_image(event->mlx_ptr, event->img.img_ptr);
	mlx_destroy_window(event->mlx_ptr, event->win_ptr);
	free_all(event);
}

int		main(int ac, char **av)
{
	t_handle_event	*begin;
	t_handle_event	*event;

	if (ac > 2)
	{
		ft_putstr("error : to many arguments, only one map is allowed.\n");
		exit(0);
	}
	event = init_event();
	begin = read_file(event, av[1]);
	set_window(begin);
}
