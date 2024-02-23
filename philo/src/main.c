/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:37:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/23 12:10:23 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include <stdlib.h>


int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_data	*data;
	bool	*status;
	//parcing;
	data = init(argv);
	//while (status)
	status = data->status;
	while (*status)
	{

	}
	return (0);
}