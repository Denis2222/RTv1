/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:03:39 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/02/13 19:15:29 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(void)
{
	//t_map		*map;
	//t_list		*list;
	t_player	*player;

	//setbuf(stdout, NULL);
	//list = read_file("./map/lvl1.w3d");
	//map = map_parse(ft_lstrev(list));
	player = newplayer(2, 2);
	setup_mlx(player);
	return (0);
}
