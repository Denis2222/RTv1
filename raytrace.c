/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:23:21 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/21 00:12:04 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float returnmax(float x, float y)
{
  if (x > y)
    return (x);
  return (y);
}

//void  spedraw();

void vectorNormalize(t_vector *v)
{
  float norm;
  float factor;

  norm =  v->x * v->x + v->y * v->y + v->z * v->z;
  if (norm > 0) {
      factor = 1 / sqrt(norm);
      v->x *= factor;
      v->y *= factor;
      v->z *= factor;
  }
}

t_ray   generatePrimRay(int x, int y, t_env *e)
{
  t_ray primRay;

  float imageAspectRatio = WIDTH / (float)HEIGHT; // assuming width > height
  float Px = (2 * ((x + 0.5) / WIDTH) - 1) * tan(e->camera.pov / 2 * M_PI / 180) * imageAspectRatio;
  float Py = (1 - 2 * ((y + 0.5) / HEIGHT) * tan(e->camera.pov / 2 * M_PI / 180));

  primRay.start = vector_new(0, 0, 0);
  primRay.dir = vector_new(Px, Py, -1);

  vectorNormalize(&primRay.dir);

  return primRay;
}

bool solveQuadratic(float a, float b, float c, float *x0, float *x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    else if (discr == 0) {
      *x0 = - 0.5 * b / a;
      *x1 = - 0.5 * b / a;
    }
    else {
        float q = (b > 0) ?
            -0.5 * (b + sqrt(discr)) :
            -0.5 * (b - sqrt(discr));
        *x0 = q / a;
        *x1 = c / q;
    }
    if (*x0 > *x1) {
      float tmp;

      tmp = *x0;
      *x0 = *x1;
      *x1 = tmp;
    }
    return true;
}

bool intersect(t_ray *ray, t_object *object, float *dist)
{
  float t0, t1;

  //printf("%f", *dist);
  t_vector L = vector_sub(ray->start, object->pos);
  float a = vector_dot(ray->dir, ray->dir);
  float b = 2 * vector_dot(ray->dir, L);
  float c = vector_dot(L, L) - (object->radius * object->radius);
  if (!solveQuadratic(a,b,c, &t0, &t1))
    return false;

    printf(" %f %f %f", t0,t1, *dist);

  if (t0 < 0)
  {
    t0 = t1;
    if (t0 < 0)
      return (false);
  }
  if (t0 < *dist)
    *dist = t0;

  return (true);
}

bool trace(t_ray *ray, t_env *e, t_object *hitObject, float *min)
{
  t_object *current;
  float cdist;

  cdist = *min;
  current = e->objects;
  while (current)
  {
    if (intersect(ray, current, &cdist))
    {
      if (cdist < *min)
      {
        *min = cdist;
        hitObject = current;
      }
    }
    current = current->next;
  }

  if (hitObject != NULL)
    return (1);
  return (0);
}

t_vector castRay(t_ray *ray, t_env *e)
{
  t_object  *hitObject;
  float     min;
  t_vector  color;

  hitObject = NULL;
  color = vector_add(ray->dir, vector_new(1,1,1));
  color = vector_scale(color, 1);
  min = 20000;
  if (trace(ray, e, hitObject, &min))
  {

    printf(" %p ", hitObject);
    color = vector_scale(color, min);
  }
  return (color);
}

void	raytrace(t_env *e)
{
  int	x;
  int	y;
  t_vector  hitColor;

  x = 0;
  while (x < WIDTH) {
    y = 0;
    while (y < HEIGHT) {
      t_ray primRay;
      primRay = generatePrimRay(x, y, e);
      hitColor = castRay(&primRay, e);
      draw_dot(e, x, y, rgb2i(hitColor.x, hitColor.y, hitColor.z));
      //fflush(stdout);
      y+=e->key.res;
    }
    x+=e->key.res;
  }
}
