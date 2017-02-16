/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:03:39 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 19:10:09 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void init(t_env *e)
{
	e->objects = NULL;
	e->objects = object_add(&(e->objects), object_new(SPHERE));
	e->objects = object_add(&(e->objects), object_new(SPHERE));
	e->objects = object_add(&(e->objects), object_new(SPHERE));
	e->objects = object_add(&(e->objects), object_new(SPHERE));
	e->objects = object_add(&(e->objects), object_new(SPHERE));
	e->objects = object_add(&(e->objects), object_new(SPHERE));
	e->objects = object_add(&(e->objects), object_new(SPHERE));
	e->objects = object_add(&(e->objects), object_new(SPHERE));
/*
	e->lights[0].pos.x = 0;
	e->lights[0].pos.y = 0;
	e->lights[0].pos.z = 20;
	e->lights[0].dir.x = 0;
	e->lights[0].dir.y = 0;
	e->lights[0].dir.z = -1;
	e->lights[0].intensity = 10;
	e->lights[0].color.x = 200;
	e->lights[0].color.y = 0;
	e->lights[0].color.z = 0;

*/
	e->camera.pov = 45;
	e->camera.pos.x = 0;
	e->camera.pos.y = 0;
	e->camera.pos.z = 0;

	e->camera.dir.x = 0;
	e->camera.dir.y = 0;
	e->camera.dir.z = -1;

	  //vectorPrint(&e->scene.objects[0].pos);
}

int		get_loop_hook(t_env *e)
{
	render(e);
	return (0);
}

int	main(void)
{
	t_env	e;

	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "RTv1");
	initkeyboard(&e);
	e.bpp = 0;
	e.size_line = 0;
	e.endian = 0;
	init(&e);
	mlx_hook(e.win, 2, 1, key_press_hook, &e);
	mlx_hook(e.win, 3, 1, key_release_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop_hook(e.mlx, &get_loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

void	render(t_env *e)
{
	key_up_down(e);
	key_left_right(e);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->imgpx = mlx_get_data_addr(e->img,
	&(e->bpp), &(e->size_line), &(e->endian));
	printf("NB objet: %d", object_count(e->objects));
	raytrace(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	usleep(50);
	mlx_destroy_image(e->mlx, e->img);
}
