/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:08:42 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/08 07:52:08 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

vector	*newcoord(float x, float y, float z)
{
	vector *coord;

	coord = malloc(sizeof(vector));
	coord->x = x;
	coord->y = y;
	coord->y = z;
	return (coord);
}
