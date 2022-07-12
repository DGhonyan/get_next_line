/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:56:10 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/09 17:56:12 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_nl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (s[i] == '\n');
}

static size_t	line_len(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] && s[len] != '\n')
		len++;
	return (len + (s[len] == '\n'));
}

static char	*remove_line(char *s)
{
	int		i;
	int		j;
	char	*res;

	if (!s)
		return (NULL);
	res = malloc (sizeof (*res) * (ft_strlen(s) - line_len(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	i += s[i] == '\n';
	while (s[i])
		res[j++] = s[i++];
	free(s);
	res[j] = '\0';
	return (res);
}

static char	*get_line(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	line = malloc(sizeof (*line) * (line_len(s) + 1));
	if (!line)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s = NULL;
	char		*line;
	char		temp[BUFFER_SIZE + 1];
	int			a;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	a = 1;
	while (a > 0)
	{
		a = read(fd, temp, BUFFER_SIZE);
		if (a == -1 || (a == 0 && (!s || s[0] == '\0')))
		{
			free(s);
			s = NULL;
			return (NULL);
		}
		temp[a] = '\0';
		s = ft_strjoin(s, temp);
		if (has_nl(s))
			break ;
	}
	line = get_line(s);
	s = remove_line(s);
	return (line);
}

// int main()
// {
// 	int fd = open ("gnlTester/files/big_line_no_nl", O_RDONLY);

// 	int i = 5;
// 	while (i--)
// 		printf("%s", get_next_line(fd));
// }