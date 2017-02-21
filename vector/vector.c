/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 01:46:57 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/21 08:16:25 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
/*
void multVecMatrix(t_vector *src, t_vector *dst)
{
    float x[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    float a, b, c, w;
    a = src.x * x[0][0] + src.y * x[1][0] + src.z * x[2][0] + x[3][0];
    b = src.x * x[0][1] + src.y * x[1][1] + src.z * x[2][1] + x[3][1];
    c = src.x * x[0][2] + src.y * x[1][2] + src.z * x[2][2] + x[3][2];
    w = src.x * x[0][3] + src.y * x[1][3] + src.z * x[2][3] + x[3][3];

    dst.x = a / w;
    dst.y = b / w;
    dst.z = c / w;
}

void multDirMatrix(t_vector *src, t_vector *dst)
{
    float x[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    float a, b, c, w;
    a = src.x * x[0][0] + src.y * x[1][0] + src.z * x[2][0] + x[3][0];
    b = src.x * x[0][1] + src.y * x[1][1] + src.z * x[2][1] + x[3][1];
    c = src.x * x[0][2] + src.y * x[1][2] + src.z * x[2][2] + x[3][2];
    w = src.x * x[0][3] + src.y * x[1][3] + src.z * x[2][3] + x[3][3];

    dst.x = a;
    dst.y = b;
    dst.z = c;
}
*/

void	vectorNormalize(t_vector *v)
{
	float norm;
	float factor;

	norm = v->x * v->x + v->y * v->y + v->z * v->z;
	if (norm > 0)
	{
		factor = 1 / sqrt(norm);
		v->x *= factor;
		v->y *= factor;
		v->z *= factor;
	}
}

t_vector vector_new(float x, float y, float z)
{
  t_vector new;

  new.x = x;
  new.y = y;
  new.z = z;
  return (new);
}

t_vector vector_rand(int max, int neg)
{
  t_vector new;

  new = vector_new((rand() % max) + neg + 0, (rand() % max) + neg , (rand() % max) + neg - 50);
  return (new);
}

void vectorPrint(t_vector vector)
{
  printf("Vect:%f/%f/%f\n", vector.x, vector.y, vector.z);
}

t_vector vector_add(t_vector v1, t_vector v2)
{
  return (vector_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector vector_sub(t_vector v1, t_vector v2)
{
  return (vector_new(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector vector_scale(t_vector v, float r)
{
  return vector_new(v.x * r, v.y * r, v.z * r);
}

float vector_dot(t_vector v1, t_vector v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
