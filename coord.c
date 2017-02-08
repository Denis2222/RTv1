/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:08:42 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/08 05:56:06 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_coord	*newcoord(double x, double y)
{
	t_coord *coord;

	coord = malloc(sizeof(t_coord));
	coord->x = x;
	coord->y = y;
	return (coord);
}
