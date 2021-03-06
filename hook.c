/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:58:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/13 19:22:38 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		key_press_hook(int keycode, t_env *e)
{
	ft_printf("[%d]", keycode);
	key_press(&e->key, keycode);
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_SPACEBAR)
		e->hud[0].c++;
	return (0);
}

int		key_release_hook(int keycode, t_env *e)
{
	key_release(&e->key, keycode);
	return (0);
}

int		expose_hook(t_env *e)
{
	render(e);
	return (0);
}
