/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exits_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:44:37 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/24 03:01:59 by ide-dieg         ###   ########.fr       */
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
 * ENAMETOOLONG = 126 - nombre de archivo demasiado largo
 * 
 * 127 - no se encontro el comando
 */
void	ft_pid_exit_with_error(void)
{
	ft_alloc_lst(0, 0);
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC
		|| errno == ENAMETOOLONG)
		exit(126);
	exit(127);
}

void	ft_exit_fork(pid_t *pids, t_pipex *pipex)
{
	int i;

	i = 0;
	perror("fork");
	ft_close_pipes(pipex);
	while (pids[i])
	{
		waitpid(pids[i], 0, 0);
		i++;
	}
	ft_alloc_lst(0, 0);
	exit(1);
}

void	ft_exit_pipe(void)
{
	perror("pipe error");
	ft_alloc_lst(0, 0);
	exit(129);
}

void	ft_exit_command_not_found(t_pipex *pipex, int i)
{
	ft_dprintf(2, "%s: command not found\n", pipex->cmds[i][0]);
	ft_close_pipes(pipex);
	ft_alloc_lst(0, 0);
	exit(127);
}
