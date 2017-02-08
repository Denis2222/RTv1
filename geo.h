/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:02:25 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/08 05:55:37 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEO_H
# define GEO_H

#include <stdbool.h> /* Needed for boolean datatype */

/* The vector structure */
typedef struct{
      float x,y,z;
}vector;

typedef struct{
        vector start;
        vector dir;
}ray;

/* Sphere Primitive definition */
typedef struct{
        vector pos;
        float radius;
        int material;
}sphere;

/* Colour definition */
typedef struct{
        float red, green, blue;
}colour;

/* Light definition */
typedef struct{
        vector pos;
        colour intensity;
}light;

/* Material definition */
typedef struct{
    colour diffuse;
    float reflection;
}material;

#endif
