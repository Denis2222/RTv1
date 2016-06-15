/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 22:31:07 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/06/16 01:44:49 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#

t_vec4		vec4(double x, double y, double z, double w)
{
	t_vec4 new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = w;
	return (new);
}

t_vec2		vec2(double x, double y)
{
	t_vec2 new;

	new.x = x;
	new.y = y;
	return (new);
}

t_camera	camera(t_vec4 position, t_vec4 orientation,
					double focale, t_vec2 pitch)
{
	t_camera new;

	new.position = position;
	new.orientation = orientation;
	new.pitch = pitch;
	new.focale = focale;
	new.resolution = vec2(WIDTH, HEIGHT);
	return (new);
}

int			main(void)
{
	t_camera	cam;

	cam = camera(
		vec4(1.0, 2.0, 3.0, 0.0),
		vec4(1.0, 1.2, 3.0, 1.0),
		1.0,
		vec2(1.0, 1.0)
	);
	printf("%f", cam.orientation.y);
	return (0);
}
