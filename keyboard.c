/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 13:52:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/08 07:08:36 by dmoureu-         ###   ########.fr       */
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
			e->player->pos->y += e->player->dir->y * MOVESPEED;
			e->player->pos->x += e->player->dir->x * MOVESPEED;
	}
	if (e->key.down)
	{
			e->player->pos->y -= e->player->dir->y * MOVESPEED;
			e->player->pos->x -= e->player->dir->x * MOVESPEED;
	}
}

void	key_left_right(t_env *e)
{
	double olddirx;
	double oldplanex;

	olddirx = e->player->dir->x;
	oldplanex = e->player->plane->x;
	if (e->key.left)
	{
		e->player->dir->x = e->player->dir->x * C_R - e->player->dir->y * S_R;
		e->player->dir->y = olddirx * S_R + e->player->dir->y * C_R;
		e->player->plane->x = e->player->plane->x
			* C_R - e->player->plane->y * S_R;
		e->player->plane->y = oldplanex * S_R + e->player->plane->y * C_R;
	}
	if (e->key.right)
	{
		e->player->dir->x = e->player->dir->x * CR - e->player->dir->y * SR;
		e->player->dir->y = olddirx * SR + e->player->dir->y * CR;
		e->player->plane->x = e->player->plane->x
			* CR - e->player->plane->y * SR;
		e->player->plane->y = oldplanex * SR + e->player->plane->y * CR;
	}
}
