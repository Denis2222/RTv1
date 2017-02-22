/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:35:31 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/21 08:17:29 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light *light_new(float x, float y, float z) {
  t_light *new;

  new = (t_light*)malloc(sizeof(t_light));
  if (!new)
    return (NULL);

  new->pos = vector_new(x, y, z);
  new->dir = vector_new(0,0,1);
  vectorNormalize(&new->dir);
  new->type = 1;
  new->color = vector_new(255, 0, 0);
  new->intensity = 0.5;
  new->next = NULL;
  return (new);
}

t_light *light_add(t_light **lst, t_light *new)
{
  t_light	*beginlst;
	t_light	*current;

	beginlst = *lst;
	current = beginlst;
	if (!*lst)
		beginlst = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (beginlst);
}

int light_count(t_light *lst)
{
  t_light *current;
  int nb;

  nb = 0;
  if (!lst)
    return (0);
  else {
    current = lst;
    nb = 1;
    while (current->next)
    {
      nb++;
      current = current->next;
    }
  }
  return (nb);
}
