/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:05:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/07 17:40:34 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlennl(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}
t_Bool	ft_check1(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!(s[i] == '0' || s[i] == '1' || s[i] == 'C' || s[i] == 'E'
				|| s[i] == 'P' || s[i] == '\n'))
			return (False);
		i++;
	}
	return (True);
}

int	ft_countchr(char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			n++;
		i++;
	}
	return (n);
}

t_Bool	ft_check2(char *s, t_Bool last_line)
{
	static int	c;
	static int	e;
	static int	p;

	if (!c)
		c = 0;
	if (!e)
		e = 0;
	if (!p)
		p = 0;
	c += ft_countchr(s, 'C');
	e += ft_countchr(s, 'E');
	p += ft_countchr(s, 'P');
	if (e > 1)
		return (False);
	if (last_line)
	{
		if (e > 1 || c < 1 || p != 1)
			return (False);
	}
	return (True);
}
t_Bool	ft_check3(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '1')
			return (False);
		i++;
	}
	return (True);
}
t_Bool	ft_check4(char *s)
{
	if ( s[0] != '1' || s[ft_strlennl(s) - 1] != '1')
		return (False);
	return (True);
}

int	ft_count_line(void)
{
	int		fd;
	char	*line;
	int		n;

	fd = open(MAP, O_RDWR);
	line = get_next_line(fd);
	n = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		n++;
	}
	close(fd);
	return (n);
}
t_Bool	ft_check(t_vars *data)
{
	size_t	line_length;
	size_t	i;

	i = 0;
	line_length = ft_strlennl(data->map->map[i]);
	if (!ft_check1(data->map->map[i]) || !ft_check2(data->map->map[i], False) || !ft_check3(data->map->map[i]))
	{
		printf("CHARACTER PROBLEM\nEXITING THE PROGRAM\n");
		return (False);
	}
	while (i < data->map->size)
	{
		if (!ft_check1(data->map->map[i]) || !ft_check2(data->map->map[i], False)
			|| !ft_check4(data->map->map[i]))
		{
			printf("CHARACTER PROBLEM\nEXITING THE PROGRAM\n");
			return (False);
		}
		if (line_length != ft_strlennl(data->map->map[i]))
		{
			printf("\nNON AUTHORIZED SHAPE\nEXITING THE PROGRAM\n");
			return (False);
		}
		i++;
	}
	if (!ft_check2(data->map->map[i - 1], True) || !ft_check3(data->map->map[i - 1]))
	{
		printf("Error\n");
		return (False);
	}
	return (True);
}

void	ft_freetab(char **s, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_convmap(t_vars *data)
{
	int		fd;
	int		i;
	char	**map;
	int		nline;

	nline = ft_count_line();
	map = (char **)malloc(nline * sizeof(char *));
	fd = open(MAP, O_RDWR);
	i = 0;
	map[i++] = get_next_line(fd);
	while (i < nline)
	{
		map[i++] = get_next_line(fd);
	}
	close(fd);
	data->map->map = map;
	data->map->size = nline;
	ft_check(data);
}
