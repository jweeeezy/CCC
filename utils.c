/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:17:17 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/02 16:22:49 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ccc.h"					// needed for t_input, MACROS
#include "libft.h"					// needed for ft_*()
#include "libme.h"					// needed for ft_*()
#include "get_next_line_bonus.h"	// needed for get_next_line()

void	init_t_input(t_input *input)
{
	input->vector = NULL;
	input->counter_tourneys = 0;
	input->counter_fighters = 0;
	input->rocks = 0;
	input->papers = 0;
	input->scissors = 0;
}

int	fetch_first_parameters(t_input *input, int fd)
{
	char	*line;
	char	**split_args;

	line = get_next_line(fd);
	if (line == NULL)
	{
		return (ERROR);
	}
	split_args = ft_split(line, ' ');
	if (split_args == NULL)
	{
		return (ERROR);
	}
	input->counter_tourneys = ft_atoi(split_args[0]);
	input->counter_fighters = ft_atoi(split_args[1]);
	free(line);
	ft_array_str_free(split_args);
	return (EXECUTED);
}