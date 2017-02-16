/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:02:25 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 19:09:24 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
#include <stdbool.h>

# include "libft/libft.h"
# include "minilibx/mlx.h"

# define WIDTH 1800
# define HEIGHT 1360

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
  t_vector 				pos;
  t_vector 				dir;
  float  				pov;
} 							t_camera;

typedef struct s_ray{
        t_vector start;
        t_vector dir;
}							 t_ray;

/* Colour definition */
typedef struct	s_color{
        float 	r;
				float 	g;
				float		b;
}								t_color;

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
        t_vector 			*pos;
        t_vector 			*dir;
        n_type		type;
        float  			radius;
        float  			albedo;
				t_color 		*color;
		    float  			reflection;
		    float  			ambient;
				struct s_object		*next;
}              			t_object;

/* Light definition */
typedef struct 	s_light{
        t_vector 	pos;
        t_vector 	dir;
        float		intensity;
        t_vector 	color;
				struct 	s_light	*next;
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

float vectorDot(t_vector *v1, t_vector *v2);
t_vector vectorSub(t_vector *v1, t_vector *v2);
t_vector vectorScale(float c, t_vector *v);
t_vector vectorAdd(t_vector *v1, t_vector *v2);
float vectorLength(t_vector *v);
void vectorNormalize(t_vector *v);
void vectorPrint(t_vector *v);

void vectorRotate(t_vector *v, char type, double angle);

bool intersectRaySphere(t_ray *r, t_object *s, float *t);

bool findIntersect(t_ray *r, float *t, t_object *objects, int *material, t_ray *newray);
void findLightIntersect(float coef, t_vector *color, t_object *objects, t_light *lights, t_ray *ray);

t_vector *vector_new(float x, float y, float z);
t_vector *vector_rand(int max, int neg);


t_object *object_new(n_type type);
t_object *object_add(t_object **lst, t_object *new);
int object_count(t_object *lst);

bool intersectObject(t_object object, t_ray *primRay, float *t);

t_color *new_color(int r, int g, int b);

#endif
