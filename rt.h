/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:02:25 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/20 21:07:58 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
#include <stdbool.h>

# include "libft/libft.h"
# include "minilibx/mlx.h"

# define WIDTH 1024
# define HEIGHT 840

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACEBAR 49

# define KEY_K 40
# define KEY_L 37

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define KEY_PLUS 69
# define KEY_MINUS 78

# define MOVESPEED 0.05
# define ROTSPEED 0.1

# define CR cos(ROTSPEED)
# define SR sin(ROTSPEED)
# define C_R cos(-ROTSPEED)
# define S_R sin(-ROTSPEED)

typedef struct	s_keyboard
{
	int						up;
	int						down;
	int						left;
	int						right;
	int						sleft;
	int						sright;
	int						res;

	int						rup;
	int						rdown;
	int						rleft;
	int						rright;
}								t_keyboard;

/* The vector structure */
typedef struct	s_vector{
      float 		x;
			float 		y;
			float 		z;
} 							t_vector;

typedef struct 	s_camera {
  t_vector 			pos;
  t_vector 			dir;
  float  				pov;
} 							t_camera;

typedef struct 	s_ray{
        				t_vector start;
        				t_vector dir;
}							 	t_ray;

typedef enum e_objtype
{
	SPHERE,
	PLAN,
	CONE,
	TRIANGLE
}	n_type;

/* Sphere Primitive definition */
typedef struct 			s_object
{
	t_vector 					pos;
	t_vector 					dir;
	t_vector 					color;

	n_type						type;
	float  						radius;
	float  						albedo;
	float  						reflection;
	float  						ambient;
	struct s_object		*next;
}              			t_object;

/* Light definition */
typedef struct 	s_light{
      t_vector 	pos;
      t_vector 	dir;
      float			intensity;
      t_vector 	color;
			struct 		s_light	*next;
}								t_light;

typedef struct	s_env
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*imgpx;
	int						bpp;
	int						size_line;
	int						endian;
	t_keyboard		key;

	t_camera      camera;
	t_light       *lights;
	t_object      *objects;
}								t_env;

void			setup_mlx();
int				key_press_hook(int keycode, t_env *e);
int				key_release_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);
void			draw_dot(t_env *e, int x, int y, int color);
int				rgb2i(int r, int g, int b);
void			initkeyboard(t_env *e);
void			key_press(t_keyboard *key, int keycode);
void			key_release(t_keyboard *key, int keycode);
void			key_up_down(t_env *e);
void			key_left_right(t_env *e);
void			render(t_env *e);
void			raytrace(t_env *e);

void vectorRotate(t_vector *v, char type, double angle);

t_vector vector_new(float x, float y, float z);
t_vector vector_rand(int max, int neg);
t_vector vector_add(t_vector v1, t_vector v2);
t_vector vector_sub(t_vector v1, t_vector v2);
t_vector vector_scale(t_vector v, float scale);
float vector_dot(t_vector v1, t_vector v2);

void vectorPrint(t_vector vector);

t_object *object_new(n_type type, float x, float y, float z);
t_object *object_add(t_object **lst, t_object *new);
t_object *object_new_random(n_type type);
int object_count(t_object *lst);

#endif
