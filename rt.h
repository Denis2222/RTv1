/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:02:25 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/15 01:35:17 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
#include <stdbool.h>

# include "libft/libft.h"
# include "minilibx/mlx.h"

# define WIDTH 1100
# define HEIGHT 800

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACEBAR 49

# define KEY_RSHIFT 258
# define KEY_LSHIFT 257

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14

# define KEY_U 32
# define KEY_I 34
# define KEY_O 31
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37

# define KEY_R 15
# define KEY_T 17
# define KEY_Y 16
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4

# define KEY_PLUS 69
# define KEY_MINUS 78

# define MOVESPEED 0.05
# define ROTSPEED 0.1

# define CR cos(ROTSPEED)
# define SR sin(ROTSPEED)
# define C_R cos(-ROTSPEED)
# define S_R sin(-ROTSPEED)

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
	DISC,
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
	float						radius2;
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
			int				type;
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
	int						resolution;
	int						*key;
  int           keyhook;

	t_camera      camera;
	t_light       *lights;
	t_light				*selectedLight;
	t_object      *objects;
	t_object			*selectedObject;
	t_vector			bgcolor;
}								t_env;

typedef struct	s_matrix
{
	float 				x[4][4];
}								t_matrix;

void			setup_mlx();
void      parse_scene(t_env *e, char *filename);
int				key_press_hook(int keycode, t_env *e);
int				key_release_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);
void			draw_dot(t_env *e, int x, int y, int color);
int				rgb2i(int r, int g, int b);
void			initkeyboard(t_env *e);
void			key_bind(t_env *e);
void			render(t_env *e);
void			raytrace(t_env *e);

void 			vectorRotate(t_vector *v, char type, double angle);

t_vector 	vector_new(float x, float y, float z);
t_vector 	vector_rand(int max, int neg);
t_vector 	vector_add(t_vector v1, t_vector v2);
t_vector vector_add_color(t_vector v1, t_vector v2);
t_vector 	vector_sub(t_vector v1, t_vector v2);
t_vector 	vector_scale(t_vector v, float scale);
float 		vector_dot(t_vector v1, t_vector v2);
void			vectorNormalize(t_vector *v);
t_vector reflect(t_vector I,t_vector N);

void 			vectorPrint(t_vector vector);

t_object 	*object_new(n_type type, float x, float y, float z);
t_object 	*object_add(t_object **lst, t_object *new);
t_object 	*object_new_random(n_type type);
t_object 	*object_new_plane(float x, float y, float z, float rx, float ry, float rz);
t_object 	*object_new_disc(float x, float y, float z, float rx, float ry, float rz);
int 			object_count(t_object *lst);

t_light 	*light_new(float x, float y, float z);
t_light 	*light_add(t_light **lst, t_light *new);
int 			light_count(t_light *lst);

t_ray ray_new(t_vector start, t_vector dir);

void 			multVecMatrix(t_vector *src, t_vector *dst);
void 			multDirMatrix(t_vector *src, t_vector *dst);


t_vector castRay(t_ray *ray, t_env *e, int depth);

#endif
