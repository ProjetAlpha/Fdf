/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 20:50:52 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 18:49:42 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 1200
# define PROJ 1
# define CAM 0
# define PROJ_P 5
# define PROJ_ISO 6
# define ROT_Y 2
# define ROT_X 3
# define ROT_Z 4
# define PI 3.14159265358979323846
# define INT_MAX (int) ((unsigned) -1 / 2)
# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))

enum	e_flag
{
	DOWN = 125,
	UP = 126,
	RIGHT = 124,
	LEFT = 123,
	ROT_Z_RIGHT = 65,
	ROT_Z_LEFT = 82,
	ZOOM_IN = 4,
	ZOOM_OUT = 5,
	MOVE_LEFT = 0,
	MOVE_RIGHT = 2,
	MOVE_DOWN = 1,
	MOVE_UP = 13,
	MOVE_FORWARD = 12,
	MOVE_BACKWARD = 7,
	NEXT_COLOR = 69,
	PREV_COLOR = 78,
	PERSPCT_PROJ = 35,
	ORTHO_PROJ = 31,
	ISO_PROJ = 34,
	RESET = 15,
	UP_Z = 258,
	DOWN_Z = 36,
	EXIT = 53
};

typedef struct		s_vec3
{
	double x;
	double y;
	double z;
	double w;
}					t_vec3;

typedef struct		s_vec2
{
	int x;
	int y;
}					t_vec2;

typedef struct		s_line
{
	t_vec2	p1;
	t_vec2	p2;
	int		inc_value;
	int		color1;
	int		color2;
	int		color3;
	int		y_longer;
	double	curr_z;
	double	mult_diff;
}					t_line;

typedef struct		s_calc
{
	double	mat_proj[4][4];
	double	world_cam[4][4];
	double	ortho_mat[4][4];
	double	y_rotation[4][4];
	double	x_rotation[4][4];
	double	z_rotation[4][4];
}					t_calc;

typedef struct		s_points
{
	t_vec3			vec;
	int				is_end;
	struct s_points *next;
}					t_points;

typedef struct		s_map
{
	t_points		*points;
	int				line_width;
	struct s_map	*next;
}					t_map;

typedef struct		s_moove
{
	int x;
	int y;
	int z;
}					t_moove;

typedef struct		s_rotate
{
	int x;
	int y;
	int z;
}					t_rotate;

typedef struct		s_img
{
	void	*img_ptr;
	int		*data;
	int		bpp;
	int		size_l;
	int		endian;
}					t_img;

typedef struct		s_handle_event
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			map_height;
	int			map_width;
	int			win_width;
	int			win_height;
	int			max_depth;
	int			min_depth;
	int			min_x;
	int			max_x;
	int			min_y;
	int			max_y;
	t_map		*map;
	t_img		img;
	int			flag;
	int			zoom;
	int			high;
	int			proj;
	int			color_rank;
	t_moove		cam_moove;
	t_rotate	cam_rot;
	t_calc		calc;
}					t_handle_event;

t_calc				reset_proj_matrix(t_calc calc);
t_handle_event		*read_file(t_handle_event *event, char *map);
t_handle_event		*init_event(void);
int					mouse_press(int button, int x, int y, void *param);
int					key_press(int keycode, void *param);
void				set_points(t_handle_event *event);
int					create_rgba(int r, int g, int b, int a);
void				draw_line(t_handle_event *event, t_line line, int color);
void				smooth_z(t_handle_event *event, int keycode);
t_calc				set_ortho_matrix(t_handle_event *event,
		float far, float near);
void				change_proj(t_handle_event *event,
		int keycode);
void				line_parsing_util(t_handle_event *event,
		t_points *begin, int c_x);
void				exit_window(t_handle_event *event, int keycode);
t_map				*init_map(void);
int					lerp(int a, int b, double lerp);
int					is_rot(t_handle_event *event);
t_vec3				get_next_vec(t_map *line, t_vec3 curr_vec);
int					is_outside(int x, int y);
t_calc				set_look_at(t_vec3 cam,
		t_vec3 target, t_vec3 up, t_calc calc);
t_calc				mult_m4(t_calc calc, double src1[4][4], double src2[4][4]);
void				reset_img(t_handle_event *event);
void				set_img(t_handle_event *event);
void				handle_color(int keycode, t_handle_event *event);
void				reset(t_vec3 vec);
void				free_all(t_handle_event *event);
t_points			*init_points(void);
t_calc				init_calc(void);
t_vec3				init_vec(void);
t_rotate			init_rot(void);
t_moove				init_moove(void);
int					dist(int xa, int xb, int ya, int yb);
void				free_pnts(t_points *points);
t_vec3				calc_rot(t_handle_event *event, t_vec3 src);
t_calc				set_mat_y(t_calc calc, double angle);
t_calc				set_mat_x(t_calc calc, double angle);
t_calc				set_mat_z(t_calc calc, double angle);
t_vec3				mult_rot_z(t_calc calc, t_vec3 curr_vec3);
t_vec3				mult_rot_x(t_calc calc, t_vec3 curr_vec3);
t_vec3				mult_rot_y(t_calc calc, t_vec3 curr_vec3);
t_vec3				mult_cam(t_calc calc, t_vec3 curr_vec3);
t_vec3				mult_proj(t_calc calc, t_vec3 curr_vec3);
int					is_end(char *line);
t_calc				set_perpective_mat(t_calc calc, double deg,
		double near, double far);
t_calc				set_camera(t_handle_event *event,
		t_calc calc, int n_elem, int scale);
t_vec3				mult_matrix(t_calc calc, t_vec3 curr_vec3, int type);
t_calc				init_calc(void);
t_vec3				init_vec(void);
int					choose_color(double curr_z, double next_z);
int					get_color(int index, int type);
t_line				set_horizontal_pnt(t_line line, t_handle_event *event,
		t_points *pnt_head, t_vec3 curr_vec);
t_line				set_vertical_pnt(t_line line,
		t_handle_event *event, t_points *pnt_head, t_vec3 curr_vec);

#endif
