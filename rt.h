/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 22:31:54 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/06/14 00:56:31 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIDTH 640
# define HEIGHT 480

# include "libft/libft.h"

typedef struct	s_vec4
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec4;

typedef	struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_camera
{
	t_vec4		*position;
	t_vec4		*orientation;
	t_vec2		*resolution;
	t_vec2		*pitch;
	double		focale;
}				t_camera;

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_material
{
	t_color		*ambiant;
	t_color		*diffuse;
	t_color		*reflexion;
	t_color		*specular;
	int			opacity;
}				t_material;

#endif
