/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_files_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:23:03 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/17 04:33:47 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_here_doc(t_pipex *pipex)
{
	char	*line;

	line = get_next_line(0);
	while (line && ft_strncmp_p(line , "here_doc\n", 9) != 0)
	{
		write(pipex->pipe_here_doc[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	else
	{
		ft_dprintf(2, "Error: here_doc not found\n");
		exit(1);
	}
	close(pipex->pipe_here_doc[1]);
}

void	ft_openfiles(t_pipex *pipex)
{
	if (ft_strncmp_p(pipex->infile, "here_doc", 8) == 0)
	{
		pipe(pipex->pipe_here_doc);
		pipex->io_fd[0] = pipex->pipe_here_doc[0];
		if (pipex->io_fd[0] < 0)
		{
			perror("here_doc");
			strerror(errno);
		}
		ft_here_doc(pipex);
		pipex->io_fd[1] = open(pipex->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->io_fd[1] < 0)
		{
			perror(pipex->outfile);
			strerror(errno);
		}
	}
	else
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
}

void	ft_closefiles(t_pipex *pipex)
{
	close(pipex->io_fd[0]);
	close(pipex->io_fd[1]);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
