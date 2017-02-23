/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:58:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 09:57:45 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		key_press_hook(int keycode, t_env *e)
{
	ft_printf("[%d]", keycode);
	//key_press(e, keycode);
	e->key[keycode] = 1;
	//(void)keycode;
	//(void)e;
	e->resolution = 5;
	e->keyhook+=2;

	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);

	return (0);
}

int		key_release_hook(int keycode, t_env *e)
{
	//(void)e;
	//key_release(e, keycode);

	printf(" {%f %f %f} \n ", e->selectedObject->pos.x, e->selectedObject->pos.y, e->selectedObject->pos.z);
	e->key[keycode] = 0;
	e->keyhook--;
	(void)keycode;
	return (0);
}

int		expose_hook(t_env *e)
{
	render(e);
	return (0);
}
