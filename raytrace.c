/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:23:21 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/21 06:40:53 by dmoureu-         ###   ########.fr       */
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
  t_vector rayOrigin;
  t_vector rayOriginWorld;
  t_vector rayPWorld;
  //t_vector rayDirection;
  t_vector rayDir;

  float imageAspectRatio = WIDTH / (float)HEIGHT; // assuming width > height
  float Px = (2 * ((x + 0.5) / WIDTH) - 1) * tan(e->camera.pov / 2 * M_PI / 180) * imageAspectRatio;
  float Py = (1 - 2 * ((y + 0.5) / HEIGHT) * tan(e->camera.pov / 2 * M_PI / 180));

  rayOrigin = vector_new(e->camera.dir.x*2, e->camera.pos.y*2, e->camera.pos.x*2); //
  rayDir = vector_new(Px, Py, -1);
  multVecMatrix(&rayOrigin, &rayOriginWorld);
  multDirMatrix(&rayDir, &rayPWorld);

  //rayDirection = vector_sub(rayPWorld, rayOriginWorld);
  vectorNormalize(&rayPWorld);

  primRay.start = rayOriginWorld;
  primRay.dir = rayPWorld;

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

bool intersectSphere(t_ray *ray, t_object *object, float *dist)
{
  float t0, t1;

  //printf("%f", *dist);
  t_vector L = vector_sub(ray->start, object->pos);
  float a = vector_dot(ray->dir, ray->dir);
  float b = 2 * vector_dot(ray->dir, L);
  float c = vector_dot(L, L) - (object->radius * object->radius);
  if (!solveQuadratic(a,b,c, &t0, &t1))
    return false;

    //printf(" %f %f %f", t0,t1, *dist);

  if (t0 < 0)
  {
    t0 = t1;
    if (t0 < 0)
      return (false);
  }
  if (t0 < *dist)
    *dist = t0;
    //printf(" %f %f %f\n", t0,t1, *dist);
  return (true);
}


bool intersectPlan(t_ray *ray, t_object *object, float *dist)
{

  float denom;
  float t;
  denom = vector_dot(object->dir, ray->dir);
  //printf("%f\n", denom);
  if (denom > 1e-6) {

     t_vector length = vector_sub(object->pos, ray->start);
     t = vector_dot(length, ray->dir) / denom;
     if (t >= 0 && t < *dist)
      *dist = t;
     return (t >= 0);
 }
 return false;
}

bool trace(t_ray *ray, t_env *e, t_object **hitObject, float *min)
{
  t_object *current;
  float cdist;

  cdist = *min;
  current = e->objects;
  while (current){
    switch ((int)current->type)
    {
      case 0:
        if (intersectSphere(ray, current, &cdist)){
          if (cdist < *min){
            *min = cdist;
            *hitObject = current;
          }
        }
      break;
      case 1:
        if (intersectPlan(ray, current, &cdist)){
          if (cdist < *min){
            *min = cdist;
            *hitObject = current;
          }
        }
      break;
    }
    current = current->next;
  }

  if (*hitObject != NULL)
    return (1);
  return (0);
}

t_vector getColor(t_ray *ray, t_env *e, t_object *hitObject, float dist)
{
  t_vector color;
  //Diffuse Shading
  t_vector hitPoint;
  t_vector normal;
  t_vector lightFromHit;

  (void)e;
  float  factor;
  // VecRayStart + VecRayDir * DistToCollide
  hitPoint = vector_add(ray->start, vector_scale(ray->dir, dist));

  if (hitObject->type == PLAN)
  {
    normal = hitObject->dir;
  } else {
    // Normal = (VecHitPoint - VecObjectPos) / R
    normal = vector_scale(vector_sub(hitPoint, hitObject->pos), (1 / hitObject->radius));
  }

  vectorNormalize(&normal);
  lightFromHit = vector_sub(hitPoint, vector_new(0,0,e->camera.dir.y*10));
  vectorNormalize(&lightFromHit);

  //Factor
  factor = vector_dot(lightFromHit, normal);
  if (factor < 0)
    factor = 0;

  color = vector_add(vector_scale(hitObject->color, factor * 0.9),vector_scale(hitObject->color, 0.1));
  return (color);
}

t_vector castRay(t_ray *ray, t_env *e)
{
  t_object  *hitObject;
  float     min;
  t_vector  color;

  hitObject = NULL;
  color = vector_add(ray->dir, vector_new(1,1,100));
  color = vector_scale(color, 50);
  //color = vector_new(30,30,30);
  min = 20000;
  if (trace(ray, e, &hitObject, &min))
  {
    color = getColor(ray, e, hitObject, min);
    //printf(" %p %f\n", hitObject, min);
    //color = hitObject->color;
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

      for (int xx = 0; xx < e->key.res; xx++){
        for (int yy = 0; yy < e->key.res; yy++){
          draw_dot(e, x+xx, y+yy, rgb2i(hitColor.x, hitColor.y, hitColor.z));
        }
      }
      //fflush(stdout);
      y+=e->key.res;
    }
    x+=e->key.res;
  }
}
