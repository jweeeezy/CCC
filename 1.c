/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:12:31 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/02 16:56:26 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ccc.h"		// needed for t_input, MACROS
#include <stdio.h>		// needed for printf()
#include <unistd.h>		// needed for read()
#include <fcntl.h>		// needed for open()
#include "libme.h"		// needed for ft_*()
#include "libft.h"		// needed for ft_*()
#include "get_next_line_bonus.h"

static t_vector_str	*handle_fight(char *line)
{
	t_vector_str	*vector;

	vector = NULL;
	if (*line == ROCK)
	{
		if (*(line + 1) == PAPER)
		{
			vector = ft_vector_str_join(vector, "P", 0);
		}
		else
		{
			vector = ft_vector_str_join(vector, "R", 0);
		}
	}
	else if (*line == PAPER)
	{
		if (*(line + 1) == SCISSORS)
		{
			vector = ft_vector_str_join(vector, "S", 0);
		}
		else
		{
			vector = ft_vector_str_join(vector, "P", 0);
		}
	}
	else if (*line == SCISSORS)
	{
		if (*(line + 1) == ROCK)
		{
			vector = ft_vector_str_join(vector, "R", 0);
		}
		else
		{
			vector = ft_vector_str_join(vector, "S", 0);
		}
	}
	return (vector);
}

static int	handle_tourney(t_input *input, int fd)
{
	int				index;
	char		 	*line;

	index = 0;
	line = get_next_line(fd);
	if (line == NULL)
	{
		return (ERROR);
	}
	while (line[index] != '\0')
	{
		input->vector = ft_vector_str_merge(input->vector,
				handle_fight(&line[index]));
		if (input->vector == NULL)
		{
			return (ERROR);
		}
		index += 2;
	}
	input->vector = ft_vector_str_join(input->vector, "\n", 0);
	return (EXECUTED);
}

int	main(int argc, char **argv)
{
	int	fd_input;
	t_input	input;

	if (argc < 2)
	{
		printf("Error! Arguments missing...\n");
		return (ERROR);
	}
	init_t_input(&input);
	fd_input = open(argv[1], O_RDONLY);
	if (fd_input < 1)
	{
		printf("Error! Couldn't open file...\n");
		return (ERROR);
	}
	if (fetch_first_parameters(&input, fd_input) == ERROR)
	{
		printf("Error! Couldn't fetch parameters...\n");
		return (ERROR);
	}
	while (input.counter_tourneys > 0)
	{
		if (handle_tourney(&input, fd_input) == ERROR)
		{
			printf("Error! Couldn't handle fights...\n");
			return (ERROR);
		}
		input.counter_tourneys -= 1;
	}
	printf("%s", input.vector->str);
	ft_vector_str_free(input.vector);
	return (EXECUTED);
}
