/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 22:54:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/13 19:24:04 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_loop_hook(t_env *e)
{
	render(e);

	return (0);
}

void	setup_mlx(t_player *player)
{
	t_env	e;

	e.player = player;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "RTv1");
	//texture_load(&e);
	//load_sprites(&e);
	initkeyboard(&e);
	e.bpp = 0;
	e.size_line = 0;
	e.endian = 0;
	mlx_hook(e.win, 2, 1, key_press_hook, &e);
	mlx_hook(e.win, 3, 1, key_release_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop_hook(e.mlx, &get_loop_hook, &e);
	mlx_loop(e.mlx);
}

void	render(t_env *e)
{
	key_up_down(e);
	key_left_right(e);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->imgpx = mlx_get_data_addr(e->img,
	&(e->bpp), &(e->size_line), &(e->endian));

	raytrace(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	usleep(500);
	mlx_destroy_image(e->mlx, e->img);
}
