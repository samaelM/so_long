/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_things.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:06:08 by maemaldo          #+#    #+#             */
/*   Updated: 2024/04/02 14:08:48 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_Bool	ft_printerror(char *error_msg)
{
	ft_printf("Error\n%s", error_msg);
	return (False);
}

void	ft_win(t_vars *data)
{
	ft_printf("\n\n\n\nGG ma boy you won\n\n\n\n");
	on_destroy(data);
}

/*
ft_print_mlx

print an image on the window

return void
*/
void	ft_print_mlx(t_vars *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, ft_min(x,
			data->map->lenght * 80), ft_min(y, data->map->size * 80));
}
