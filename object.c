/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:35:31 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/20 23:34:03 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object *object_new_random(n_type type)
{
  t_object *object;

  object = object_new(type, 0, 20, -50);
  object->pos = vector_rand(30,0);
  object->radius = 2;

  return (object);
}

t_object *object_new(n_type type, float x, float y, float z) {
  t_object *new;

  new = (t_object*)malloc(sizeof(t_object));
  if (!new)
    return (NULL);

  new->pos = vector_new(x, y, z);
  new->dir = vector_new(0,0,1);
  new->type = type;
  new->radius = 0.5;
  new->albedo = 0.18;
  new->color = vector_new(255, 0, 0);
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
