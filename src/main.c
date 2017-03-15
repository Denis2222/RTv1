/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:03:39 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/15 07:06:20 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void init(t_env *e)
{


	parse_scene(e, "./scenetest.rt");



	e->objects = NULL;


	//e->objects = object_add(&(e->objects), object_new(SPHERE, 0, 1, 0));
/*
	specialObject = object_new(SPHERE, -1, 0, -4);
	specialObject->reflection = 0.4;
	specialObject->color = vector_new(0, 0,180);
*/
	//e->objects = object_add(&(e->objects), specialObject);




	t_object *specialObject;
	specialObject = object_new(SPHERE, 1, 1, 20);
	specialObject->reflection =0.3;
	specialObject->color = vector_new(35, 200,86);
	e->objects = object_add(&(e->objects), specialObject);

	e->objects = object_add(&(e->objects), object_new_plane(vector_new(0,0,2), vector_new(0,0,-1), vector_new(150,150,250)));
	e->objects = object_add(&(e->objects), object_new_plane(vector_new(-1,0,0), vector_new(-1,0,0), vector_new(250,0,150)));

	//e->objects = object_add(&(e->objects), object_new(SPHERE, 1, -2, -2));

	//e->objects = object_add(&(e->objects), object_new_random(SPHERE));
	//e->objects = object_add(&(e->objects), object_new_random(SPHERE));
	//e->objects = object_add(&(e->objects), object_new_random(SPHERE));
	//e->objects = object_add(&(e->objects), object_new_random(SPHERE));
	//e->objects = object_add(&(e->objects), object_new_random(SPHERE));
	// e->objects = object_add(&(e->objects), object_new_random(SPHERE));

	e->keyhook = 0;
	e->lights = light_add(&(e->lights), light_new(0,0,0));

	e->lights = light_add(&(e->lights), light_new(-10,0,0));

	e->lights = light_add(&(e->lights), light_new(20,0,0));
	//e->lights = light_add(&(e->lights), light_new(0,100,0));

	e->bgcolor = vector_new(0,0,0);

	e->selectedObject = e->objects;
	e->selectedLight = e->lights;

	e->resolution = 3;
	e->camera.pov = 80;

	e->camera.pos.x = 0;
	e->camera.pos.y = 0;
	e->camera.pos.z = 13;

	e->camera.dir.x = 0;
	e->camera.dir.y = 0;
	e->camera.dir.z = 1;

	  //vectorPrint(&e->scene.objects[0].pos);
}

int		get_loop_hook(t_env *e)
{
	//printf("#%d %d\n", e->keyhook, e->resolution);
	if (e->keyhook > 0)
	{
		e->keyhook--;
		render(e);
	}
	else if (e->resolution > 1)
	{
		e->resolution--;
		render(e);
	} else {

	}
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
	//render(&e);
	mlx_loop(e.mlx);
	return (0);
}

void	render(t_env *e)
{
	key_bind(e);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->imgpx = mlx_get_data_addr(e->img,
	&(e->bpp), &(e->size_line), &(e->endian));

	raytrace(e);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	usleep(50);
	mlx_destroy_image(e->mlx, e->img);
}
