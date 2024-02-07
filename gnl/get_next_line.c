/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:04:45 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/07 12:07:41 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strjoinlst(t_list **s1, char const *s2)
{
	size_t	i;
	t_list	*temp;

	i = 0;
	while (*s1 && (*s1)->next != NULL)
	{
		s1 = &(*s1)->next;
	}
	while (s2[i])
	{
		temp = ft_lstnew(s2[i]);
		if (!temp)
			return (0);
		if (*s1)
			(*s1)->next = temp;
		else
			(*s1) = temp;
		s1 = &(*s1)->next;
		i++;
	}
	return (1);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_strchr(const t_list *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s)
	{
		if (s->content == (char)c)
			return (i);
		i++;
		s = s->next;
	}
	return (-1);
}

char	*ft_line_cleaner(t_list **s)
{
	int		len;
	char	*line;
	int		i;
	t_list	*temp;

	len = ft_strchr(*s, '\n') + 1;
	if (len <= 0)
		len = ft_lstsize(*s);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (*s != NULL && i < len)
	{
		line[i++] = (*s)->content;
		temp = (*s);
		*s = (*s)->next;
		free(temp);
	}
	line[len] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static t_list	*stash;
	size_t			n;

	if (!stash)
		stash = NULL;
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (NULL);
	n = 1;
	while (ft_strchr(stash, '\n') == -1 && n > 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (!*buff || n <= 0)
			break ;
		(n)[buff] = 0;
		if (!ft_strjoinlst(&stash, buff))
			return (NULL);
	}
	free(buff);
	if (stash == NULL)
		return (NULL);
	return (ft_line_cleaner(&stash));
}

// #include <fcntl.h>
// int main(void)
// {
// 	char *line;
// 	int i = 10;
// 	int fd = open("multiple_line_no_nl", O_RDWR);
// 	while (i > 0)
// 	{
// 		line = get_next_line(fd);
// 		// while (line)
// 		// {
// 		// 	printf("%c", line->content);
// 		// 	line = line->next;
// 		// }
// 		printf("%s", line);
// 		free(line);
// 		i--;
// 	}
// 	close(fd);
// 	return (1);
// }
