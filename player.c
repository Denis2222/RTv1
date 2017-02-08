/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:02:08 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/08 08:06:26 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		d2r(double d)
{
	return (M_PI * d / 180);
}

t_player	*newplayer()
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->pos = newcoord(0, 0, -2000);
	player->dir = newcoord(0, 0, 1);
	//fixproplane(player, 0.66);
	return (player);
}
