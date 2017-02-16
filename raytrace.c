/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:23:21 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 19:11:25 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray   generatePrimRay(int x, int y, t_env *e)
{
  t_ray primRay;

  float imageAspectRatio = WIDTH / (float)HEIGHT; // assuming width > height
  float Px = (2 * ((x + 0.5) / WIDTH) - 1) * tan(e->camera.pov / 2 * M_PI / 180) * imageAspectRatio;
  float Py = (1 - 2 * ((y + 0.5) / HEIGHT) * tan(e->camera.pov / 2 * M_PI / 180));

  primRay.dir.x = Px;
  primRay.dir.y = Py;
  primRay.dir.z = -1;

  vectorNormalize(&primRay.dir);
  return primRay;
}

bool trace(t_ray *primRay, t_env *e, float *t, t_object *hitObject)
{
  float tNear = 99999;
  //int   index = 0;
  //float uv[2];
  //vectorPrint(&e->scene.objects[0].pos);
  //Foreach objects
  if (intersectObject(e->objects[0], primRay, t) && *t < tNear)
  {
    hitObject = &e->objects[0];
    tNear = *t;
    //printf("OBJECT TROUVE %f", *t);
  }
  return (hitObject != NULL);
}

float returnmax(float x, float y)
{
  if (x > y)
    return (x);
  return (y);
}

t_color *castRay(t_ray *primRay, t_env *e){
  t_color *hitColor;
  t_object *hitObject;
  float energy;
  float t;

  hitObject = NULL;
  hitColor = new_color(150, 10, 0);
  if (trace(primRay, e, &t, hitObject))
  {
    //vectorPrint(&hitObject->pos);
    //t_vector Phit = vectorAdd(&primRay->start, &primRay->dir);
    //Phit = vectorScale(t,&Phit);
    //vector Nhit;
    //vector hitPoint = vectorScale(t,&Phit);
    //vector hitNormal = vectorSub(&Phit, hitObject->pos);
    //float hitTexCoordinates[2];
    //getSurfaceProperties(hitObject, hitPoint, primRay->dir, index, uv, &hitNormal, hitTexCoordinates   )
    //vector L = vectorScale(-1, &e->scene.lights[0].dir);

    energy = 10;//hitObject->albedo / M_PI * e->scene.lights[0].intensity * returnmax(0.f, vectorDot(&hitNormal, &L));
    //hitColor  = vectorScale(energy, &e->lights[0].color);
    //vectorPrint(&hitColor);
    //return hitColor;
  }
  //hitColor = vector_new(primRay->dir.x,primRay->dir.y,primRay->dir.z);
  return (hitColor);
}

void  spedraw();

void	raytrace(t_env *e)
{
  (void)e;

  return ;
  int	x;
  int	y;
  t_color  *hitColor;

  x = 0;
  while (x < WIDTH) {
    y = 0;
    while (y < HEIGHT) {
      //Generate Primray
      t_ray primRay;
      primRay = generatePrimRay(x, y, e);

      hitColor = castRay(&primRay, e);


      draw_dot(e, x, y, rgb2i(hitColor->r, hitColor->g, hitColor->b));


      //draw_pix(x, y, e);
      y+=e->key.res;
    }
    x+=e->key.res;
  }
}
