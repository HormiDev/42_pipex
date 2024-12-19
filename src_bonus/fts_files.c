/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:23:03 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/12/19 23:50:56 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_openfiles(t_pipex *pipex)
{
	pipex->io_fd[0] = open(pipex->infile, O_RDONLY);
	if (pipex->io_fd[0] < 0)
	{
		perror(pipex->infile);
		strerror(errno);
	}
	pipex->io_fd[1] = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->io_fd[1] < 0)
	{
		perror(pipex->outfile);
		strerror(errno);
	}
}

void	ft_closefiles(t_pipex *pipex)
{
	t_list	*tmp;

	tmp = pipex->pipes_fds;
	close(pipex->io_fd[0]);
	close(pipex->io_fd[1]);
	while (tmp)
	{
		close(((int *)tmp->content)[0]);
		close(((int *)tmp->content)[1]);
		tmp = tmp->next;
	}
}
