/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:08:52 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/11 00:59:36 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void ft_executions(t_pipex *pipex) {
    int fd[2];
    pid_t pid;
    int cmd = 0;
    int infile_fd, outfile_fd;

    // Abrir el archivo de entrada
    infile_fd = open(pipex->infile, O_RDONLY);
    if (infile_fd < 0) {
        perror("Error al abrir el archivo de entrada");
        exit(EXIT_FAILURE);
    }

    while (pipex->cmds[cmd]) {
        if (pipe(fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            if (cmd == 0) {
                // Primer comando: redirigir la entrada desde infile
                dup2(infile_fd, 0);
                close(infile_fd);
            } else {
                // Comandos intermedios: redirigir la entrada desde la tubería anterior
                dup2(pipex->pipe_fd[0], 0);
                close(pipex->pipe_fd[0]);
            }
            if (pipex->cmds[cmd + 1] == 0) {
                // Último comando: redirigir la salida a outfile
                outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (outfile_fd < 0) {
                    perror("Error al abrir el archivo de salida");
                    exit(EXIT_FAILURE);
                }
                dup2(outfile_fd, 1);
                close(outfile_fd);
            } else {
                // Comandos intermedios: redirigir la salida a la tubería
                dup2(fd[1], 1);
                close(fd[1]);
            }
            execve(pipex->cmds[cmd][0], pipex->cmds[cmd], 0);
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
        } else {
            // Proceso padre: cerrar descriptores de archivo y esperar al hijo
            close(fd[1]);
            if (cmd > 0) {
                close(pipex->pipe_fd[0]);
            }
            pipex->pipe_fd[0] = fd[0];
            waitpid(pid, 0, 0);
            cmd++;
        }
    }
    close(infile_fd);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
	{
		ft_putstr_fd("\033[0;31mError\n\033[0;33mUsage: ./pipex", 2);
		ft_putstr_fd(" file1 cmd1 cmd2 file2\n\033[0m", 2);
		return (1);
	}
	pipex = ft_parsing_pipex(argc, argv, envp);
	ft_executions(pipex);
	ft_alloc_lst(0, 0);
	return 0;
}