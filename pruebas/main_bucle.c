/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bucle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:15:48 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/20 16:27:02 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"

int	main(int argc, char **argv)
{
	int	fd;	
	int	i;

	if (argc != 2)
	{
		ft_putstr_fd("\033[0;31mError\n\033[0;33mUsage: ./main_bucle <seconds>\n\033[0m", 2);
		return (1);
	}
	i = ft_atoi(argv[1]);
	fd = open("bucle.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (i > 0)
	{
		ft_printf("%d segundos\n", i);
		ft_putstr_fd("bucle \n", fd);
		sleep(1);
		i--;
	}
	return (0);
}
