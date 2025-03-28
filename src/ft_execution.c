/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:46:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/24 19:27:53 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pid_1(t_pipex *pipex, char **envp)
{
	int	infile;

	infile = open(pipex->infile, O_RDONLY);
	if (infile < 0)
	{
		perror(pipex->infile);
		ft_closefiles(pipex);
		ft_alloc_lst(0, 0);
		exit(1);
	}
	if (ft_strchr(pipex->cmds[0][0], '/') == NULL)
	{
		ft_dprintf(2, "%s: command not found\n", pipex->cmds[0][0]);
		ft_closefiles(pipex);
		ft_alloc_lst(0, 0);
		exit(127);
	}
	dup2(infile, 0);
	dup2(pipex->pipe_fd[1], 1);
	close(infile);
	ft_closefiles(pipex);
	execve(pipex->cmds[0][0], pipex->cmds[0], envp);
	perror(pipex->cmds[0][0]);
	ft_pid_exit_with_error();
}

void	ft_pid_2(t_pipex *pipex, char **envp)
{
	int	outfile;

	outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror(pipex->outfile);
		ft_closefiles(pipex);
		ft_alloc_lst(0, 0);
		exit(1);
	}
	if (ft_strchr(pipex->cmds[1][0], '/') == NULL)
	{
		ft_dprintf(2, "%s: command not found\n", pipex->cmds[1][0]);
		ft_closefiles(pipex);
		ft_alloc_lst(0, 0);
		exit(127);
	}
	dup2(pipex->pipe_fd[0], 0);
	dup2(outfile, 1);
	ft_closefiles(pipex);
	close(outfile);
	execve(pipex->cmds[1][0], pipex->cmds[1], envp);
	perror(pipex->cmds[1][0]);
	ft_pid_exit_with_error();
}

void	ft_wait_pids(pid_t pid1, pid_t pid2)
{
	int		last_exit_cmd_status;

	waitpid(pid1, &last_exit_cmd_status, 0);
	waitpid(pid2, &last_exit_cmd_status, 0);
	if (WIFSIGNALED(last_exit_cmd_status))
	{
		ft_alloc_lst(0, 0);
		exit(128 + WTERMSIG(last_exit_cmd_status));
	}
	if (WIFEXITED(last_exit_cmd_status))
	{
		ft_alloc_lst(0, 0);
		exit(WEXITSTATUS(last_exit_cmd_status));
	}
}

void	ft_executions(t_pipex *pipex, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipex->pipe_fd) < 0)
		ft_exit_pipe();
	pid1 = fork();
	if (pid1 < 0)
		ft_exit_fork();
	if (pid1 == 0)
		ft_pid_1(pipex, envp);
	pid2 = fork();
	if (pid2 < 0)
		ft_exit_fork();
	if (pid2 == 0)
		ft_pid_2(pipex, envp);
	ft_closefiles(pipex);
	ft_wait_pids(pid1, pid2);
}
