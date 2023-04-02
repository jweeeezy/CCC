/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:15:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/02 17:11:36 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ccc.h"					// needed for t_input, MACROS
#include <stdio.h>					// needed for printf()
#include <unistd.h>					// needed for read()
#include <fcntl.h>					// needed for open()
#include "libme.h"					// needed for ft_*()
#include "libft.h"					// needed for ft_*()
#include "get_next_line_bonus.h"	// needed for get_next_line()

static int	fetch_amount_of_fighting_styles(t_input *input, int fd_input)
{
	char 	*line;
	char	**array;

	line = get_next_line(fd_input);
	if (line == NULL)
	{
		return (ERROR);
	}
	array = ft_split(line, ' ');
	if (array == NULL)
	{
		free(line);
		return (ERROR);
	}
	free(line);
	input->rocks = ft_atoi(array[0]);
	input->papers = ft_atoi(array[1]);
	input->scissors = ft_atoi(array[2]);
	ft_array_str_free(array);
	return (EXECUTED);
}

static int	determine_matchups(t_input *input)
{
	while (input->rocks > 0)
	{
		if (input->rocks >= 3)
		{
			input->vector = ft_vector_str_join(input->vector, "RRRP", 0);
			if (input->vector == NULL)
			{
				return (ERROR);
			}
			input->rocks -= 3;
			input->papers -= 1;
		}
		else if (input->rocks >= 2)
		{
			input->vector = ft_vector_str_join(input->vector, "RPR", 0);
			if (input->vector == NULL)
			{
				return (ERROR);
			}
			input->rocks -= 2;
			input->papers -= 1;
		}
		else
		{
			input->vector = ft_vector_str_join(input->vector, "R", 0);
			input->rocks -= 1;
		}
	}
	while (input->papers > 0)
	{
		input->vector = ft_vector_str_join(input->vector, "P", 0);
		if (input->vector == NULL)
		{
			return (ERROR);
		}
		input->papers -= 1;
	}
	while (input->scissors > 0)
	{
		input->vector = ft_vector_str_join(input->vector, "S", 0);
		if (input->vector == NULL)
		{
			return (ERROR);
		}
		input->scissors -= 1;
	}
	return (EXECUTED);
}

static int	seed_tourney(t_input *input, int fd_input)
{
	if (fetch_amount_of_fighting_styles(input, fd_input) == ERROR)
	{
		return (ERROR);
	}
	if (determine_matchups(input) == ERROR)
	{
		return (ERROR);
	}
	input->vector = ft_vector_str_join(input->vector, "\n", 0);
	if (input->vector == NULL)
	{
		return (ERROR);
	}
	return (EXECUTED);
}

static int	setup_tourneys(t_input *input, int fd_input)
{
	int	index;

	index = 0;
	while(index < input->counter_tourneys)
	{
		if (seed_tourney(input, fd_input) == ERROR)
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
	if (setup_tourneys(&input, fd_input) == ERROR)
	{
		return (ERROR);
	}
	printf("%s", input.vector->str);
	ft_vector_str_free(input.vector);
	//system("leaks exec_level3");
	return (EXECUTED);
}