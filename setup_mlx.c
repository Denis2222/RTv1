/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 22:54:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/08 07:31:33 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))

/* Multiply two vectors and return the resulting scalar (dot product) */

float vectorDot(vector *v1, vector *v2){
        return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/* Subtract two vectors and return the resulting vector */

vector vectorSub(vector *v1, vector *v2){
       vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
       return result;
}

/* Calculate Vector x Scalar and return resulting Vector*/
vector vectorScale(float c, vector *v){
        vector result = {v->x * c, v->y * c, v->z * c };
        return result;
}

/* Add two vectors and return the resulting vector */
vector vectorAdd(vector *v1, vector *v2){
        vector result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
        return result;
}

/* Check if the ray and sphere intersect */
bool intersectRaySphere(ray *r, sphere *s, float *t){

        bool retval = false;

        /* A = d.d, the vector dot product of the direction */
        float A = vectorDot(&r->dir, &r->dir);

        /* We need a vector representing the distance between the start of
         * the ray and the position of the circle.
         * This is the term (p0 - c)
         */
        vector dist = vectorSub(&r->start, &s->pos);

        /* 2d.(p0 - c) */
        float B = 2 * vectorDot(&r->dir, &dist);

        /* (p0 - c).(p0 - c) - r^2 */
        float C = vectorDot(&dist, &dist) - (s->radius * s->radius);

        /* Solving the discriminant */
        float discr = B * B - 4 * A * C;

        /* If the discriminant is negative, there are no real roots.
         * Return false in that case as the ray misses the sphere.
         * Return true in all other cases (can be one or two intersections)
         *  t, the solution to the equation represents the closest point
         * where our ray intersects with the sphere.
         */
        if(discr < 0)
                retval = false;
        else{
                float sqrtdiscr = sqrtf(discr);
                float t0 = (-B + sqrtdiscr)/(2);
                float t1 = (-B - sqrtdiscr)/(2);

                /* We want the closest one */
                if(t0 > t1)
                        t0 = t1;

                /* Verify t0 larger than 0 and less than the original t */
                if((t0 > 0.001f) && (t0 < *t)){
                        *t = t0;
                        retval = true;
                }else
                        retval = false;
        }

return retval;
}

void	raytrace(t_env *e)
{

	material materials[3];
	materials[0].diffuse.red = 1;
	materials[0].diffuse.green = 0;
	materials[0].diffuse.blue = 0;
	materials[0].reflection = 0;

	materials[1].diffuse.red = 0;
	materials[1].diffuse.green = 1;
	materials[1].diffuse.blue = 0;
	materials[1].reflection = 0.5;

	materials[2].diffuse.red = 0;
	materials[2].diffuse.green = 0;
	materials[2].diffuse.blue = 1;
	materials[2].reflection = 0.9;

	sphere spheres[3];
	spheres[0].pos.x = 200;
	spheres[0].pos.y = 300;
	spheres[0].pos.z = 0;
	spheres[0].radius = 100;
	spheres[0].material = 0;

	spheres[1].pos.x = 400;
	spheres[1].pos.y = 400;
	spheres[1].pos.z = 100;
	spheres[1].radius = (float)e->player->dir->y*1000;
	spheres[1].material = 1;

	spheres[2].pos.x = 500;
	spheres[2].pos.y = 140;
	spheres[2].pos.z = 0;
	spheres[2].radius = 50;
	spheres[2].material = 2;

	light lights[3];

	lights[0].pos.x = 0;
	lights[0].pos.y = 240;
	lights[0].pos.z = -100;
	lights[0].intensity.red = 1;
	lights[0].intensity.green = 1;
	lights[0].intensity.blue = 1;

	lights[1].pos.x = 3200;
	lights[1].pos.y = 3000;
	lights[1].pos.z = -1000;
	lights[1].intensity.red = 0.6;
	lights[1].intensity.green = 0.7;
	lights[1].intensity.blue = 1;

	lights[2].pos.x = 600;
	lights[2].pos.y = 0;
	lights[2].pos.z = -100;
	lights[2].intensity.red = 0.3;
	lights[2].intensity.green = 0.5;
	lights[2].intensity.blue = 1;

	ray r;
	int	x;
	int	y;

	//float dirx = (float)e->player->pos->x;
	//float diry = (float)e->player->pos->y;
	printf("%f", (float)e->player->dir->y);

	x = 0;
	while (x < WIDTH)
	{
		//printf("%d ", x);
		y = 0;
		while (y < HEIGHT)
		{

			float red = 0;
			float green = 0;
			float blue = 0;

			int level = 0;
			float coef = 1.0;

			r.start.x = x;
			r.start.y = y;
			r.start.z = -2000;

			r.dir.x = 0;
			r.dir.y = (float)e->player->pos->y - 2.00;
			r.dir.z = 1;


						do{
							/* Find closest intersection */
							float t = 20000.0f;
							int currentSphere = -1;

							unsigned int i;
							for(i = 0; i < 3; i++){
								if(intersectRaySphere(&r, &spheres[i], &t))
									currentSphere = i;
							}
							if(currentSphere == -1) break;

							vector scaled = vectorScale(t, &r.dir);
							vector newStart = vectorAdd(&r.start, &scaled);

							/* Find the normal for this new vector at the point of intersection */
							vector n = vectorSub(&newStart, &spheres[currentSphere].pos);
							float temp = vectorDot(&n, &n);
							if(temp == 0) break;

							temp = 1.0f / sqrtf(temp);
							n = vectorScale(temp, &n);

							/* Find the material to determine the colour */
							material currentMat = materials[spheres[currentSphere].material];

							/* Find the value of the light at this point */
							unsigned int j;
							for(j=0; j < 3; j++){
								light currentLight = lights[j];
								vector dist = vectorSub(&currentLight.pos, &newStart);
								if(vectorDot(&n, &dist) <= 0.0f) continue;
								float t = sqrtf(vectorDot(&dist,&dist));
								if(t <= 0.0f) continue;

								ray lightRay;
								lightRay.start = newStart;
								lightRay.dir = vectorScale((1/t), &dist);

								/* Lambert diffusion */
								float lambert = vectorDot(&lightRay.dir, &n) * coef;
								red += lambert * currentLight.intensity.red * currentMat.diffuse.red;
								green += lambert * currentLight.intensity.green * currentMat.diffuse.green;
								blue += lambert * currentLight.intensity.blue * currentMat.diffuse.blue;
							}
							/* Iterate over the reflection */
							coef *= currentMat.reflection;

							/* The reflected ray start and direction */
							r.start = newStart;
							float reflect = 2.0f * vectorDot(&r.dir, &n);
							vector tmp = vectorScale(reflect, &n);
							r.dir = vectorSub(&r.dir, &tmp);

							level++;

						}while((coef > 0.0f) && (level < 15));

						if (red > 0.00 || green > 0.00 || blue > 0.00){
							draw_dot(e, x, y, rgb2i(red*255, green*255, blue*255));
							//printf("COLOR!!!{%f|%f|%f} ", red*255, green*255, blue*255);
						}


			y++;
		}
		x++;
	}
}

int		get_loop_hook(t_env *e)
{
	render(e);

	return (0);
}

void	setup_mlx(t_player *player, t_map *map)
{
	t_env	e;

	e.map = map;
	e.player = player;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "RTv1");
	//texture_load(&e);
	//load_sprites(&e);
	initkeyboard(&e);
	e.bpp = 0;
	e.size_line = 0;
	e.endian = 0;
	mlx_hook(e.win, 2, 1, key_press_hook, &e);
	mlx_hook(e.win, 3, 1, key_release_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop_hook(e.mlx, &get_loop_hook, &e);
	mlx_loop(e.mlx);
}

void	render(t_env *e)
{
	key_up_down(e);
	key_left_right(e);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->imgpx = mlx_get_data_addr(e->img,
	&(e->bpp), &(e->size_line), &(e->endian));
	//raycast(e);
	raytrace(e);
	printf("RayTraceFinish");
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	//usleep(5000000);
	mlx_destroy_image(e->mlx, e->img);
}