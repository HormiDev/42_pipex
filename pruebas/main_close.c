/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:59:15 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/23 15:57:43 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int fd;

	fd = -10;
	while (1)
	{
		printf("fd = %d\n", fd);
		write(1, "close\n", 6);
		close(fd);
		fd++;
	}
	return (0);
}