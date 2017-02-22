/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 23:23:52 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 09:07:42 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rgb2i(int r, int g, int b)
{
	int	color;

	color = 256 * 256 * r;
	color += 256 * g;
	color += b;
	return (color);
}

void	draw_dot(t_env *e, int x, int y, int color)
{
	char	b;
	char	g;
	char	r;
	int		i;

	if (color == 256 * 256 * 256 + 256 * 256 + 256)
		return ;
	b = color % 256;
	g = (color / 256) % 256;
	r = (color / 256 / 256) % 256;
	i = (e->size_line * y) + (x * (e->bpp / 8));

	if (i < (WIDTH * HEIGHT * e->bpp / 8))
	{
		e->imgpx[i] = b;
		e->imgpx[i + 1] = g;
		e->imgpx[i + 2] = r;
	}
}
