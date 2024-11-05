/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:25:05 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/05 01:35:34 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"

int main(int argc, char **argv)
{
	int fd;
	int fd2;
	char *line;

	if (argc != 2)
	{
		ft_printf("Usage: %s <file>\n", argv[0]);
		return 1;
	}
	fd = open(argv[1], O_RDONLY);
	fd2 = dup(fd);
	line = get_next_line(fd);
	ft_printf("line: %s\n", line);
	free(line);
	line = get_next_line(fd2);
	ft_printf("line: %s\n", line);
	line = get_next_line(fd);
	ft_printf("line: %s\n", line);
	free(line);
	close(fd2);
	fd2 = dup(fd);
	line = get_next_line(fd2);
	ft_printf("line: %s\n", line);
	free(line);
	line = get_next_line(fd);
	ft_printf("line: %s\n", line);
	free(line);
	close(fd2);
	dup2(fd, fd2);
	line = get_next_line(fd2);
	ft_printf("line: %s\n", line);

	
	free(line);
	close(fd);
	close(fd2);
	get_next_line(-1);
	return 0;
}