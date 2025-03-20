/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:11:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/20 04:28:55 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_read_here_doc(char *limiter, int here_doc_fd)
{
	char	*line;

	ft_printf("%s > ", limiter);
	line = get_next_line(0);
	line[ft_strlen_p(line) - 1] = '\0';
	while (line && ft_strncmp_p(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		ft_dprintf(here_doc_fd, "%s\n", line);
		free(line);
		ft_printf("%s > ", limiter);
		line = get_next_line(0);
		if (line)
			line[ft_strlen_p(line) - 1] = '\0';
	}
	if (line)
		free(line);
	else
	{
		ft_dprintf(2, "\nwarning: here-document at line 1 delimited by");
		ft_dprintf(2, " end-of-file (wanted «%s»)\n", limiter);
	}
}

void	ft_here_doc(char *limiter)
{
	int 	here_doc_fd;

	here_doc_fd = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (here_doc_fd == -1)
	{
		perror("open");
		ft_alloc_lst(0, 0);
		exit(1);
	}
	ft_read_here_doc(limiter, here_doc_fd);
	close(here_doc_fd);
	get_next_line(-1);
}
