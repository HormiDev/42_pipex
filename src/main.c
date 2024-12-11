/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:29:55 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/12/11 03:50:07 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void	ft_executions(t_pipex *pipex, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	pid_t	pid1;
	pid_t	pid2;
	int		last_exit_cmd_status;
	
	infile_fd = open(pipex->infile, O_RDONLY);
	if (infile_fd < 0)
	{
		perror(pipex->infile);
		strerror(errno);
	}
	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror(pipex->outfile);
		strerror(errno);
	}
	pipe(pipex->pipe_fd);
	pid1 = fork();
	if (pid1 < 0)
	{
		ft_putstr_fd("Error al crear el proceso hijo\n", 2);
		exit(1);
	}
	if (pid1 == 0)
	{
		if (infile_fd < 0)
			exit(127);
		dup2(infile_fd, 0);
		dup2(pipex->pipe_fd[1], 1);
		close(infile_fd);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		execve(pipex->cmds[0][0], pipex->cmds[0], envp);
		perror(pipex->cmds[0][0]);
		exit(127);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		ft_putstr_fd("Error al crear el proceso hijo\n", 2);
		exit(1);
	}
	if (pid2 == 0)
	{
		if (outfile_fd < 0)
			exit(1);
		dup2(pipex->pipe_fd[0], 0);
		dup2(outfile_fd, 1);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		close(outfile_fd);
		execve(pipex->cmds[1][0], pipex->cmds[1], envp);
		perror(pipex->cmds[1][0]);
		exit(127);
	}
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(infile_fd);
	close(outfile_fd);
	waitpid(pid1, &last_exit_cmd_status, 0);
	waitpid(pid2, &last_exit_cmd_status, 0);
	if (WIFEXITED(last_exit_cmd_status))
	{
		ft_alloc_lst(0, 0);
		exit(WEXITSTATUS(last_exit_cmd_status));
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
	{
		ft_putstr_fd("\033[0;31mError\n\033[0;33mUsage: ./pipex", 2);
		ft_putstr_fd(" file1 cmd1 cmd2 file2\n\033[0m", 2);
		return (1);
	}
	pipex = ft_parsing_pipex(argc, argv, envp);
	ft_executions(pipex, envp);
	ft_alloc_lst(0, 0);
	return (0);
}