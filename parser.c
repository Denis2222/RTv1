/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 22:00:42 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/14 22:18:17 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void parse_scene(t_env *e, char *filename)
{
  (void)e;

  int		fd;
  	char	*line;
  	int		i;

  if ((fd = open(filename, O_RDONLY)) < 0)
  	{
  		ft_putstr("nofile");
  	}
  	else
  	{
  		i = 1;
  		while ((i = get_next_line(fd, &line) > 0))
  		{
  			printf("%s\n", line);
  			free(line);
  		}
  	}
}
