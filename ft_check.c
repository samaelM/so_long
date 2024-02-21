/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:12:33 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/20 12:30:12 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_Bool	ft_printerror(char *error_msg)
{
	printf("Error\n%s", error_msg);
	return (False);
}

t_Bool	ft_check1(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!(s[i] == '0' || s[i] == '1' || s[i] == 'C' || s[i] == 'E'
				|| s[i] == 'P' || s[i] == '\n'))
			return (ft_printerror(ERROR1));
		i++;
	}
	return (True);
}

t_Bool	ft_check2(t_map *data, char *s, t_Bool last_line)
{
	data->c += ft_countchr(s, 'C');
	data->e += ft_countchr(s, 'E');
	data->p += ft_countchr(s, 'P');
	if (data->e > 1)
		return (ft_printerror(ERROR2));
	if (last_line)
	{
		if (data->e < 1)
			return (ft_printerror(ERROR3));
		if (data->c < 1)
			return (ft_printerror(ERROR4));
		if (data->p != 1)
			return (ft_printerror(ERROR5));
	}
	return (True);
}

t_Bool	ft_check3(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (ft_printerror(ERROR10));
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '1')
			return (ft_printerror(ERROR6));
		i++;
	}
	return (True);
}

t_Bool	ft_check4(char *s)
{
	if (s[0] != '1' || s[ft_strlennl(s) - 1] != '1')
		return (ft_printerror(ERROR6));
	return (True);
}
