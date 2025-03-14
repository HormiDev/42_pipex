/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:46:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/14 03:43:42 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief funcion que hace exit con el error correspondiente
 * 
 * EAACCS = 126 - no tiene permisos de ejecucion
 * EISDIR = 126 - es un directorio
 * ENOEXEC = 126 - no es un archivo ejecutable o esta corrupto
 * ETXTBSY = 126 - archivo bloqueado por otro proceso            REVISAR
 * ENOMEM = 126 - no hay suficiente memoria                      REVISAR
 * 
 * 127 - no se encontro el comando
 */
void	ft_pid_exit_with_error(void)
{
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC)
		exit(126);
	exit(127);
}

void	ft_pid_1(t_pipex *pipex, char **envp)
{
	if (pipex->io_fd[0] < 0 || pipex->cmds[0][0] == NULL)
		exit(127);
	dup2(pipex->io_fd[0], 0);
	dup2(pipex->pipe_fd[1], 1);
	close(pipex->io_fd[0]);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	execve(pipex->cmds[0][0], pipex->cmds[0], envp);
	perror(pipex->cmds[0][0]);
	ft_pid_exit_with_error();
}

void	ft_pid_2(t_pipex *pipex, char **envp)
{
	if (pipex->io_fd[1] < 0)
		exit(1);
	if (pipex->cmds[1][0] == NULL)
		exit(127);
	dup2(pipex->pipe_fd[0], 0);
	dup2(pipex->io_fd[1], 1);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->io_fd[1]);
	execve(pipex->cmds[1][0], pipex->cmds[1], envp);
	perror(pipex->cmds[1][0]);
	ft_pid_exit_with_error();
}

void	ft_wait_pids(pid_t pid1, pid_t pid2)
{
	int		last_exit_cmd_status;

	waitpid(pid1, &last_exit_cmd_status, 0);
	waitpid(pid2, &last_exit_cmd_status, 0);
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

	ft_openfiles(pipex);
	pipe(pipex->pipe_fd);
	pid1 = fork();
	if (pid1 < 0)
	{
		ft_putstr_fd("Error al crear el proceso hijo\n", 2);
		exit(1);
	}
	if (pid1 == 0)
		ft_pid_1(pipex, envp);
	pid2 = fork();
	if (pid2 < 0)
	{
		ft_putstr_fd("Error al crear el proceso hijo\n", 2);
		exit(1);
	}
	if (pid2 == 0)
		ft_pid_2(pipex, envp);
	ft_closefiles(pipex);
	ft_wait_pids(pid1, pid2);
}
