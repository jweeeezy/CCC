/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:06:00 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/02 17:10:22 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ccc.h"		// needed for t_input, MACROS
#include <stdio.h>		// needed for printf()
#include <unistd.h>		// needed for read()
#include <fcntl.h>		// needed for open()
#include "libme.h"		// needed for ft_*()
#include "libft.h"		// needed for ft_*()
#include "get_next_line_bonus.h"	// needed for get_next_line()

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

static int	handle_round(t_input *input)
{
	int				index;
	t_vector_str	*result;

	index = 0;
	result = NULL;
	while (index < input->counter_fighters && input->vector->str[index] != '\0' && input->vector->str[index] != '\n')
	{
		result = ft_vector_str_merge(result, handle_fight(&input->vector->str[index]));
		if (result == NULL)
		{
			return (ERROR);
		}
		index += 2;
	}
	ft_vector_str_free(input->vector);
	input->vector = result;
	return (EXECUTED);
}

static int	handle_tourney(t_input *input, int fd)
{
	int				index;
	char			*line;

	index = 0;
	line = get_next_line(fd);
	input->vector = ft_vector_str_new(line);
	free(line);
	if (input->vector == NULL || input->vector == NULL)
	{
		return (ERROR);
	}
	while (index < ROUNDS)
	{
		if (handle_round(input) == ERROR)
		{
			return (ERROR);
		}
		index += 1;
	}
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
		printf("%s\n", input.vector->str);
		ft_vector_str_free(input.vector);
		input.vector = NULL;
	}
	close(fd_input);
	system("leaks exec_level2");
	return (EXECUTED);
}