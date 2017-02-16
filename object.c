/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:35:31 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 19:10:21 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object *object_new(n_type type) {
  t_object *new;

  new = (t_object*)malloc(sizeof(t_object));
  if (!new)
    return (NULL);

  new->pos = vector_rand(200, -350);
  new->dir = vector_new(0,0,1);
  new->type = type;
  new->radius = 10;
  new->albedo = 0.18;
  new->color = new_color(255, 0, 0);
  new->reflection = 0;
  new->ambient = 0;
  new->next = NULL;
  return (new);
}

t_object *object_add(t_object **lst, t_object *new)
{
  t_object	*beginlst;
	t_object	*current;

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

int object_count(t_object *lst)
{
  t_object *current;
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
