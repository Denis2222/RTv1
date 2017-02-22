/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 13:52:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/21 04:12:58 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	initkeyboard(t_env *e)
{
	int i;

	e->key = (int*)malloc(sizeof(int) * 256);
	i = 0;
	while (i < 256)
	{
		e->key[i] = 0;
		i++;
	}
}

void	key_bind(t_env *e)
{
	if (e->key[KEY_I]){
			e->camera.pos.y += 1;
	}
	if (e->key[KEY_K]){
			e->camera.pos.y -= 1;
	}
	if (e->key[KEY_J]){
		e->camera.pos.x -= 1;
	}
	if (e->key[KEY_L]){
		e->camera.pos.x += 1;
	}
	if (e->key[KEY_U]){
			e->camera.pos.z -= 1;
	}
	if (e->key[KEY_O]){
			e->camera.pos.z += 1;
	}

	if (e->key[KEY_W]){
			e->selectedLight->pos.x += 2;
	}

	if (e->key[KEY_S]){
			e->selectedLight->pos.x -= 2;
	}

	if (e->key[KEY_A]){
			e->selectedLight->pos.y += 2;
	}

	if (e->key[KEY_D]){
			e->selectedLight->pos.y -= 2;
	}

	if (e->key[KEY_Q]){
			e->selectedLight->pos.z += 2;
	}

	if (e->key[KEY_E]){
			e->selectedLight->pos.z -= 2;
	}

	if (e->key[KEY_F]){
			e->selectedObject->pos.x += 2;
	}

	if (e->key[KEY_H]){
			e->selectedObject->pos.x -= 2;
	}

	if (e->key[KEY_T]){
			e->selectedObject->pos.y += 2;
	}

	if (e->key[KEY_G]){
			e->selectedObject->pos.y -= 2;
	}

	if (e->key[KEY_R]){
			e->selectedObject->pos.z += 2;
	}

	if (e->key[KEY_Y]){
			e->selectedObject->pos.z -= 2;
	}


	if (e->key[KEY_UP]){
		t_light *light;

		light = e->selectedLight;
		if (light->next)
			e->selectedLight = light->next;
		else
			e->selectedLight = e->lights;
	}

	if (e->key[KEY_RIGHT]){
		t_object *object;

		object = e->selectedObject;
		if (object->next)
			e->selectedObject = object->next;
		else
			e->selectedObject = e->objects;
	}

	if (e->key[KEY_PLUS]){
			e->resolution -= 1;
	}
	if (e->key[KEY_MINUS]){
			e->resolution += 1;
	}
	if (e->resolution < 1)
		e->resolution = 1;

(void)e;
}
