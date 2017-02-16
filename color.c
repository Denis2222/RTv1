/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:53:38 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 18:55:22 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color *new_color(int r, int g, int b)
{
  t_color *color;

  color = (t_color*)malloc(sizeof(t_color));
  color->r = r;
  color->g = g;
  color->b = b;
  return (color);
}
