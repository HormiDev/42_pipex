/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ide-dieg <ide-dieg@student.42madrid>	   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/07 18:08:52 by ide-dieg		  #+#	#+#			 */
/*   Updated: 2024/11/12 18:41:52 by ide-dieg		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	ft_executions(t_pipex *pipex)
{
	int		fd[2];
	pid_t	pid;
	int		cmd;
	int		infile_fd;
	int		outfile_fd;
	int		i;
	int		last_exit_status;

	cmd = 0;
	i = 0;
	infile_fd = open(pipex->infile, O_RDONLY); // Abrir el archivo de entrada
	if (infile_fd < 0)
	{
		ft_putstr_fd("Error al abrir el archivo de entrada", 2);
		exit(127);
	}
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
			}
			else
			{ // Comandos intermedios: redirigir la entrada desde la tubería anterior
				dup2(pipex->pipe_fd[0], 0);
				close(pipex->pipe_fd[0]);
			}
			if (pipex->cmds[cmd + 1] == 0)
			{ // Último comando: redirigir la salida a outfile
				outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
			execve(pipex->cmds[cmd][0], pipex->cmds[cmd], 0);
			ft_putstr_fd("\033[0;33mcommand not found: ", 2);
			ft_putstr_fd(pipex->cmds[cmd][0], 2);
			ft_putstr_fd("\033[0m\n", 2);
			exit(EXIT_FAILURE);
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
			if (i >= pipex->n_cmds)
				while (i > 0)
				{
					wait(&last_exit_status);
					i--;
				}
		}
		
	}
	close(infile_fd);
	return (last_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("\033[0;31mError\n\033[0;33mUsage: ./pipex", 2);
		ft_putstr_fd(" file1 cmd1 cmd2 file2\n\033[0m", 2);
		return (1);
	}
	pipex = ft_parsing_pipex(argc, argv, envp);
	exit_status = ft_executions(pipex);
	ft_alloc_lst(0, 0);
	exit (exit_status);
}