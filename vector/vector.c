/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 01:46:57 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/16 18:53:05 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_vector *vector_new(float x, float y, float z)
{
  t_vector *new;

  new = (t_vector *)malloc(sizeof(t_vector));
  new->x = x;
  new->y = y;
  new->z = z;
  return (new);
}

t_vector *vector_rand(int max, int neg)
{
  t_vector *new;

  new = vector_new((rand() % max) - neg, (rand() % max) - neg, (rand() % max) - neg);
  return (new);
}

/* Multiply two vectors and return the resulting scalar (dot product) */
float vectorDot(t_vector *v1, t_vector *v2){
        return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/* Subtract two vectors and return the resulting vector */

t_vector vectorSub(t_vector *v1, t_vector *v2){
       t_vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
       return result;
}

/* Calculate Vector x Scalar and return resulting Vector*/
t_vector vectorScale(float c, t_vector *v){
        t_vector result = {v->x * c, v->y * c, v->z * c };
        return result;
}

/* Add two vectors and return the resulting vector */
t_vector vectorAdd(t_vector *v1, t_vector *v2){
        t_vector result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
        return result;
}

float vectorLength(t_vector *v){
  return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

void vectorNormalize(t_vector *v){
  float len = vectorLength(v);
  float factor;
    if(len == 0.0f)
        return ;
    else
    {
        factor = 1.0f / len;
        v->x *= factor;
        v->y *= factor;
        v->z *= factor;
    }
}

void vectorPrint(t_vector *v) {
  printf(" Vect:[%f %f %f]", v->x, v->y, v->z);
}

void vectorRotateX(t_vector *v, double angle){
  double rad = angle / M_PI;
  t_vector new;
  float matrixrotx[3][3] = 	{{1, 0, 0                }, {0, cos(rad) , sin(rad)  }, {0, -sin(rad),  cos(rad)}};

  new.x = matrixrotx[0][0] * v->x + matrixrotx[1][0] * v->y + matrixrotx[2][0] * v->z;
  new.y = matrixrotx[0][1] * v->x + matrixrotx[1][1] * v->y + matrixrotx[2][1] * v->z;
  new.z = matrixrotx[0][2] * v->x + matrixrotx[1][2] * v->y + matrixrotx[2][2] * v->z;

  v->x = new.x;
  v->y = new.y;
  v->z = new.z;
}

void vectorRotateY(t_vector *v, double angle){
  double rad = angle / M_PI;
  t_vector new;
  float matrixroty[3][3] = 	{{cos(rad), 0 , -sin(rad)}, {0, 1, 0                 }, {sin(rad), 0, cos(rad)  }};

  new.x = matrixroty[0][0] * v->x + matrixroty[1][0] * v->y + matrixroty[2][0] * v->z;
  new.y = matrixroty[0][1] * v->x + matrixroty[1][1] * v->y + matrixroty[2][1] * v->z;
  new.z = matrixroty[0][2] * v->x + matrixroty[1][2] * v->y + matrixroty[2][2] * v->z;

  v->x = new.x;
  v->y = new.y;
  v->z = new.z;
}

void vectorRotateZ(t_vector *v, double angle){
  double rad = angle / M_PI;
  t_vector new;
  float matrixrotz[3][3] = 	{{cos(rad) ,sin(rad) , 0 }, {-sin(rad) , cos(rad) , 0}, {0, 0, 1                }};

  new.x = matrixrotz[0][0] * v->x + matrixrotz[1][0] * v->y + matrixrotz[2][0] * v->z;
  new.y = matrixrotz[0][1] * v->x + matrixrotz[1][1] * v->y + matrixrotz[2][1] * v->z;
  new.z = matrixrotz[0][2] * v->x + matrixrotz[1][2] * v->y + matrixrotz[2][2] * v->z;

  v->x = new.x;
  v->y = new.y;
  v->z = new.z;
}

/*
** Vector Rotation
*/
void vectorRotate(t_vector *v, char type, double angle){
  if (type == 'x')
    vectorRotateX(v, angle);
  if (type == 'y')
    vectorRotateY(v, angle);
  if (type == 'z')
    vectorRotateZ(v, angle);
}

bool solveQuadratic(float a, float b, float c, float *x0, float *x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    else if (discr == 0) {
      *x0 = (float)(- 0.5 * b / a);
      *x1 = (float)(- 0.5 * b / a);
    }
    else {
        float q = (b > 0) ?
            -0.5 * (b + sqrt(discr)) :
            -0.5 * (b - sqrt(discr));
        *x0 = q / a;
        *x1 = c / q;
    }
    if (*x0 > *x1) {
      float tmp = *x0;
      *x0 = *x1;
      *x1 = tmp;
    }

    return true;
}

bool intersectObject(t_object object, t_ray *primRay, float *t) {
  float t0, t1; // solutions for t if the ray intersects


  t_vector L = vectorSub(&primRay->start, &object.pos);
  float a = vectorDot(&primRay->dir, &primRay->dir);

  float b = 2 * vectorDot(&primRay->dir, &L);
  float c = vectorDot(&L, &L) - (object.radius * object.radius);
  if (!solveQuadratic(a, b, c, &t0, &t1)) return false;

  if (t0 > t1) {
    float tmp = t0;
    t0 = t1;
    t1 = tmp;
  }

  if (t0 < 0) {
    t0 = t1; // if t0 is negative, let's use t1 instead
    if (t0 < 0) return false; // both t0 and t1 are negative
  }

  *t = t0;

  return true;
}
