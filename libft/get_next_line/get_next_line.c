/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:39:30 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/14 20:25:49 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Elimina el contenido hasta un salto de linea y retorna el resto.
char	*cut_after_next_line(char **str)
{
	int		i;
	int		j;
	char	*res;
	int		x;

	i = 0;
	j = 0;
	while ((*str)[i] != '\n')
		i++;
	while ((*str)[i + 1 + j] != '\0')
		j++;
	if (!j)
		return (free_out(&*str));
	res = (char *) malloc(j + 1 * sizeof(char));
	if (!res)
		return (free_out(&*str));
	x = -1;
	while (++x < j)
		res[x] = (*str)[i + 1 + x];
	res[x] = '\0';
	free(*str);
	return (res);
}

//Busca y retorna el contenido hasta el \n incluido
char	*search_for_next_line(char **saved)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = -1;
	while ((*saved)[i] != '\0' && (*saved)[i] != '\n')
		i++;
	if ((*saved)[i] == '\n')
	{
		res = malloc((++i + 1) * sizeof(char));
		if (!res)
			return (free_out(&*saved));
		while (++j < i)
			res[j] = (*saved)[j];
		res[j] = '\0';
		if (!check_stack(&*saved, i, &res))
			return (NULL);
		return (res);
	}
	return (free_out(&*saved));
}

//Funcion que concatena lo almacenado en saved con la nueva lectura de buffer
char	*ft_strcat(char **saved, char *buff, int buff_size)
{
	char	*res;
	int		i;
	int		j;
	int		s1_len;

	s1_len = 0;
	while (*saved && (*saved)[s1_len] != '\0')
		s1_len++;
	res = (char *) malloc((s1_len + buff_size + 1) * sizeof(char));
	if (!res)
		return (free_out(&*saved));
	i = 0;
	j = 0;
	while (*saved && (*saved)[j] != '\0')
		res[i++] = (*saved)[j++];
	j = 0;
	while (buff && j < buff_size)
		res[i++] = buff[j++];
	res[i] = '\0';
	free(*saved);
	return (res);
}

//Funcion que lee del archivo BUFFER_SIZE caracteres
char	*read_next_line(char **saved, int fd)
{
	int		readed;
	char	*buffer;

	buffer = malloc (BUFFER_SIZE);
	while (is_next_line(*saved) == 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			if (*saved)
				free(*saved);
			*saved = NULL;
			return (free_out(&buffer));
		}
		if (readed > 0)
		{
			*saved = ft_strcat(&*saved, buffer, readed);
			if (!*saved)
				return (free_out(&buffer));
		}
		else if (readed == 0)
			return (free_out(&buffer), *saved);
	}
	free_out(&buffer);
	return (search_for_next_line(&*saved));
}

//Funcion principal
char	*get_next_line(int fd)
{
	char				*next_line;
	static t_line_list	saved[OPEN_MAX + 1];

	if (fd < 0 || fd > OPEN_MAX + 1)
		return (NULL);
	if (saved[fd].line != NULL && is_next_line(saved[fd].line))
	{
		next_line = search_for_next_line(&saved[fd].line);
		if (!next_line)
			return (NULL);
		return (next_line);
	}
	next_line = read_next_line(&saved[fd].line, fd);
	if (!next_line)
		return (NULL);
	else if (next_line && !is_next_line(next_line))
		saved[fd].line = NULL;
	return (next_line);
}

/*
int	main(void)
{
	int	i = 1;
	int	fd1 = open("a", O_RDONLY);
	int	fd2 = open("b", O_RDONLY);

	printf("FD: %d\n", fd1);
	printf("FD: %d\n", fd2);

	printf("%d:%s\n", i, get_next_line(fd1));
	printf("%d:%s\n", i, get_next_line(fd2));
	i++;
	printf("%d:%s\n", i, get_next_line(fd1));
	printf("%d:%s\n", i, get_next_line(fd2));

	i++;
	printf("%d:%s\n", i, get_next_line(fd1));
	printf("%d:%s\n", i, get_next_line(fd2));

	i++;
	printf("%d:%s\n", i, get_next_line(fd1));
	printf("%d:%s\n", i, get_next_line(fd2));


	i++;
	printf("%d:%s\n", i, get_next_line(fd1));
	printf("%d:%s\n", i, get_next_line(fd2));


	i++;
	printf("%d:%s\n", i, get_next_line(fd1));
	printf("%d:%s\n", i, get_next_line(fd2));

	i++;
	printf("%d:%s\n", i, get_next_line(fd1));
	printf("%d:%s\n", i, get_next_line(fd2));

	i++;
	printf("%d:%s\n", i, get_next_line(fd1));
	printf("%d:%s\n", i, get_next_line(fd2));
}*/
