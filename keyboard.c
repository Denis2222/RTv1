/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 13:52:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/21 04:12:58 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	initkeyboard(t_env *e)
{
	int i;

	e->key = (int*)malloc(sizeof(int) * 256);
	i = 0;
	while (i < 256)
	{
		e->key[i] = 0;
		//ft_putnbr(e->key[i]);
		i++;
	}
}

void	key_bind(t_env *e)
{

	if (e->key[KEY_I]){
			e->camera.pos.y += 1;
	}

	if (e->key[KEY_K]){
			e->camera.pos.y -= 1;
	}
	if (e->key[KEY_J]){
		e->camera.pos.x -= 1;
	}
	if (e->key[KEY_L]){
		e->camera.pos.x += 1;
	}
	if (e->key[KEY_U]){
			e->camera.pos.z -= 1;
	}
	if (e->key[KEY_O]){
			e->camera.pos.z += 1;
	}

	if (e->key[KEY_PLUS]){
			e->resolution -= 1;
	}
	if (e->key[KEY_MINUS]){
			e->resolution += 1;
	}
	if (e->resolution < 1)
		e->resolution = 2;

(void)e;
}
