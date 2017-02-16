/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 02:39:16 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 10:02:14 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool intersectRayPlane(ray *r, t_object *p, float *t){
  float denom = vectorDot(&p->dir,&r->dir);
  float newt;
  if (denom > 0.00001f) {
    vector dist;
    dist = vectorSub(&p->pos, &r->start);
    newt = vectorDot(&dist, &p->dir) / denom;
    if (newt < *t)
    {
      *t = vectorDot(&dist, &p->dir) / denom;
    }
    return (t >= 0);
  }
  return false;
}

// /* Check if the ray and sphere intersect */
bool intersectRaySphere(ray *r, t_object *s, float *t){

        bool retval = false;

        // /* A = d.d, the vector dot product of the direction */
        float A = vectorDot(&r->dir, &r->dir);

        // /*
        // ** We need a vector representing the distance between the start of
        // ** the ray and the position of the circle.
        // ** This is the term (p0 - c)
        // */
        vector dist = vectorSub(&r->start, &s->pos);
        //
        // /*
        // ** B = 2 * ray->dir * dist(ray-><-sphere)
        // */
        float B = 2 * vectorDot(&r->dir, &dist);

        // /* (p0 - c).(p0 - c) - r^2 */
        float C = vectorDot(&dist, &dist) - (s->radius * s->radius);

        // /* Solving the discriminant */
        float discr = B * B - 4 * A * C;

        // /* If the discriminant is negative, there are no real roots.
        //  * Return false in that case as the ray misses the sphere.
        //  * Return true in all other cases (can be one or two intersections)
        //  *  t, the solution to the equation represents the closest point
        //  * where our ray intersects with the sphere.
        //  */
        if(discr < 0)
                retval = false;
        else{
                float sqrtdiscr = sqrtf(discr);
                float t0 = (-B + sqrtdiscr)/(2);
                float t1 = (-B - sqrtdiscr)/(2);

                // /* We want the closest one */
                if(t0 > t1)
                        t0 = t1;

                // /* Verify t0 larger than 0 and less than the original t */
                if((t0 > 0.001f) && (t0 < *t)){
                        *t = t0;
                        retval = true;
                }else
                        retval = false;
        }
        return retval;
}

void findLightIntersect(float coef, vector *color, t_object *objects, material *material, t_light *lights, ray *newray){


  /* Find the value of the light at this point */
  unsigned int j;
  for(j=0; j < 1; j++){
    t_light currentLight = lights[j];
    vector dist = vectorSub(&currentLight.pos, &newray->start);
    if(vectorDot(&newray->dir, &dist) <= 0.0f) continue;
    float t = sqrtf(vectorDot(&dist,&dist));
    if(t <= 0.0f) continue;

    ray lightRay;
    lightRay.start = newray->start;
    lightRay.dir = vectorScale((1/t), &dist);

    /* Calculate shadows */
    bool inShadow = false;
    unsigned int k;
    for (k = 0; k < 5; ++k) {
      if (objects[k].type == 0){
        if (intersectRaySphere(&lightRay, &objects[k], &t)){
          inShadow = true;
          break;
        }
        if (intersectRayPlane(&lightRay, &objects[k], &t)){
          inShadow = true;
          break;
        }
      }
    }
    if (!inShadow){
      /* Lambert diffusion */
      //printf("[#%f#]", coef);
      float lambert = vectorDot(&lightRay.dir, &newray->dir) * coef;
      color->x += lambert * currentLight.intensity.red * material->diffuse.red;
      color->y += lambert * currentLight.intensity.green * material->diffuse.green;
      color->z += lambert * currentLight.intensity.blue * material->diffuse.blue;
    }
  }
}

bool findIntersect(ray *r, float *t, t_object *objects, int *material, ray *newray){

  int currentObject = -1;
  //int currentPlane = -1;

  unsigned int i;
  for(i = 0; i < 3; i++){
    if (objects[i].type == 0){
      if(intersectRaySphere(r, &objects[i], t))
        currentObject = i;
    }
    if (objects[i].type == 1){
      if (intersectRayPlane(r, &objects[i],t))
        currentObject = i;
    }
  }

  // /* Find something */
	if(currentObject != -1) {

		vector scaled = vectorScale(*t, &r->dir);
		newray->start = vectorAdd(&r->start, &scaled);

		// /* Find the normal for this new vector at the point of intersection */
		newray->dir = vectorSub(&newray->start, &objects[currentObject].pos);
    float temp = vectorDot(&newray->dir, &newray->dir);
		if(temp == 0)// Si produit scalaire = 0 , stop
      return false;
    vectorNormalize(&newray->dir);

		// /* Find the material to determine the colour */
		*material = objects[currentObject].material;
    return true;
  } else
    return false;
}
