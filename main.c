/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 22:31:07 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/06/14 00:59:17 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec4		*vec4(int x, int y, int z, int w)
{
	t_vec4 *new;

	new = malloc(sizeof(t_vec4));
	new->x = x;
	new->y = y;
	new->z = z;
	new->w = w;
	return (new);
}

t_vec2		*vec2(int x, int y)
{
	t_vec2 *new;

	new = malloc(sizeof(t_vec2));
	new->x = x;
	new->y = y;
	return (new);
}

t_camera	*camera(t_vec4 *position, t_vec4 *orientation,
					double focale, t_vec2 *pitch)
{
	t_camera *new;

	new = malloc(sizeof(t_camera));
	new->position = position;
	new->orientation = orientation;
	new->pitch = pitch;
	new->focale = focale;
	new->resolution = vec2(WIDTH, HEIGHT);
	return (new);
}

int			main(void)
{

	t_camera	*cam;

	cam = camera(vec4(0, 0, 0, 1), vec4(1, 0, 0, 0), 5, vec2(1, 1));
	return (0);
}
