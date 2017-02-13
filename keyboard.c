/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 13:52:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/11 20:26:55 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	initkeyboard(t_env *e)
{
	e->key.up = 0;
	e->key.down = 0;
	e->key.left = 0;
	e->key.right = 0;
	e->key.sleft = 0;
	e->key.sright = 0;
	e->key.res = 4;
}

void	key_press(t_keyboard *key, int keycode)
{
	if (keycode == KEY_UP)
		key->up = 1;
	if (keycode == KEY_DOWN)
		key->down = 1;
	if (keycode == KEY_LEFT)
	{
		key->right = 0;
		key->left = 1;
	}
	if (keycode == KEY_RIGHT)
	{
		key->left = 0;
		key->right = 1;
	}

	if (keycode == KEY_PLUS || keycode == KEY_K)
		key->res += 1;
	if (keycode == KEY_MINUS || keycode == KEY_L)
		key->res -= 1;

	if (key->res<=0)
		key->res = 1;
		//printf(" %d  ",keycode);
}

void	key_release(t_keyboard *key, int keycode)
{
	if (keycode == KEY_UP)
		key->up = 0;
	if (keycode == KEY_DOWN)
		key->down = 0;
	if (keycode == KEY_LEFT)
		key->left = 0;
	if (keycode == KEY_RIGHT)
		key->right = 0;
}

void	key_up_down(t_env *e)
{
	if (e->key.up)
	{
			e->player->pos->x += 1;
	}
	if (e->key.down)
	{
			e->player->pos->x -= 1;
	}
}

void	key_left_right(t_env *e)
{
	if (e->key.left)
	{
		printf("WTF");
		e->player->dir->y = e->player->dir->y - 1;
	}
	if (e->key.right)
	{
		e->player->dir->y = e->player->dir->y + 1;
	}
}
