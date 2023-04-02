/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:19:18 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/02 16:22:18 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CCC_H
# define CCC_H

# define ERROR -1
# define EXECUTED 0

# define ROCK 'R'
# define PAPER 'P'
# define SCISSORS 'S'
# define ROUNDS 2

#include "libme.h"

typedef struct s_input
{
	t_vector_str	*vector;
	char			*line;
	int				counter_tourneys;
	int				counter_fighters;
	int				rocks;
	int				papers;
	int				scissors;
}			t_input;


int		fetch_first_parameters(t_input *input, int fd);
void	init_t_input(t_input *input);

#endif	// CCC_H
