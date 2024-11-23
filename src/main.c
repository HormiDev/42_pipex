/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:29:55 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/23 03:42:24 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
/*
void	ft_executions(t_pipex *pipex, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		cmd;
	int		infile_fd;
	int		outfile_fd;
	int		i;
	int		last_exit_cmd_status;
	int 	exit_status;

	last_exit_cmd_status = 0;
	cmd = 0;
	i = 0;
	infile_fd = open(pipex->infile, O_RDONLY); // Abrir el archivo de entrada
	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Abrir el archivo de salida
	if (infile_fd < 0)
		infile_fd = 0;
	while (pipex->cmds[cmd])
	{
		if (pipe(fd) == -1)
		{
			ft_putstr_fd("pipe", 2);
			exit(127);
		}
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("fork", 2);
			exit(127);
		}
		if (pid == 0)
		{
			if (cmd == 0)
			{ // Primer comando: redirigir la entrada desde infile
				dup2(infile_fd, 0);
				close(infile_fd);
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			else
			{ // Comandos intermedios: redirigir la entrada desde la tubería anterior
				dup2(pipex->pipe_fd[0], 0);
				close(pipex->pipe_fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			if (pipex->cmds[cmd + 1] == 0)
			{ // Último comando: redirigir la salida a outfile
				if (outfile_fd < 0)
				{
					ft_putstr_fd("Error al abrir el archivo de salida", 2);
					exit(127);
				}
				dup2(outfile_fd, 1);
				close(outfile_fd);
			}
			else
			{ // Comandos intermedios: redirigir la salida a la tubería
				dup2(fd[1], 1);
				close(fd[1]);
			}
			execve(pipex->cmds[cmd][0], pipex->cmds[cmd], envp);
			ft_putstr_fd("\033[0;33mcommand not found: ", 2);
			ft_putstr_fd(pipex->cmds[cmd][0], 2);
			ft_putstr_fd("\033[0m\n", 2);
			exit(127);
		}
		else
		{ // Proceso padre: cerrar descriptores de archivo y esperar al hijo
			close(fd[1]);
			if (cmd > 0)
				close(pipex->pipe_fd[0]);
			pipex->pipe_fd[0] = fd[0];
			//waitpid(pid, 0, 0);
			cmd++;
			i++;
		}
		
	}
	while (i > 0)
	{
		if(wait(&exit_status) == pid)
		{
			last_exit_cmd_status = exit_status;
			close(infile_fd);
			close(pipex->pipe_fd[0]);
			close(pipex->pipe_fd[1]);
			close(outfile_fd);
			close(fd[0]);
			close(fd[1]);
		}
		i--;
	}
	close(infile_fd);
	if (WIFEXITED(last_exit_cmd_status))
	{
		ft_alloc_lst(0, 0);
		exit(WEXITSTATUS(last_exit_cmd_status));
	}
}*/

void	ft_executions(t_pipex *pipex, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	pid_t	pid1;
	pid_t	pid2;
	int		last_exit_cmd_status;
	
	infile_fd = open(pipex->infile, O_RDONLY);
	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		{
			ft_putstr_fd("Error al abrir el archivo de entrada\n", 2);
			exit(127);
		}
		dup2(infile_fd, 0);
		dup2(pipex->pipe_fd[1], 1);
		close(infile_fd);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		execve(pipex->cmds[0][0], pipex->cmds[0], envp);
		ft_putstr_fd("\033[0;33mcommand not found: ", 2);
		ft_putstr_fd(pipex->cmds[0][0], 2);
		ft_putstr_fd("\033[0m\n", 2);
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
		dup2(pipex->pipe_fd[0], 0);
		dup2(outfile_fd, 1);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		close(outfile_fd);
		execve(pipex->cmds[1][0], pipex->cmds[1], envp);
		ft_putstr_fd("\033[0;33mcommand not found: ", 2);
		ft_putstr_fd(pipex->cmds[1][0], 2);
		ft_putstr_fd("\033[0m\n", 2);
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