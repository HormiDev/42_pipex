/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:46:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/23 19:34:49 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_pid(t_pipex *pipex, char **envp)
{
	int infile;

	infile = open(pipex->infile, O_RDONLY);
	if (infile < 0)
	{
		perror(pipex->infile);
		ft_alloc_lst(0, 0);
		exit(1);
	}
	if (ft_strchr(pipex->cmds[0][0], '/') == NULL)
	{
		ft_dprintf(2, "%s: command not found\n", pipex->cmds[0][0]);
		ft_alloc_lst(0, 0);
		exit(127);
	}
	dup2(infile, 0);
	dup2(pipex->pipeline[0][1], 1);
	close(infile);
	ft_close_pipes(pipex);
	execve(pipex->cmds[0][0], pipex->cmds[0], envp);
	perror(pipex->cmds[0][0]);
	ft_pid_exit_with_error();
}

void	ft_last_pid(t_pipex *pipex, int i, char **envp)
{
	int outfile;

	if (pipex->here_doc)
		outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror(pipex->outfile);
		exit(1);
	}
	if (ft_strchr(pipex->cmds[i][0], '/') == NULL)
	{
		ft_dprintf(2, "%s: command not found\n", pipex->cmds[i][0]);
		exit(127);
	}
	dup2(pipex->pipeline[i - 1][0], 0);
	dup2(outfile, 1);
	ft_close_pipes(pipex);
	close(outfile);
	execve(pipex->cmds[i][0], pipex->cmds[i], envp);
	perror(pipex->cmds[i][0]);
	ft_pid_exit_with_error();
}

void	ft_middle_pid(t_pipex *pipex, int i, char **envp)
{
	if (ft_strchr(pipex->cmds[i][0], '/') == NULL)
	{
		ft_dprintf(2, "%s: command not found\n", pipex->cmds[i][0]);
		exit(127);
	}
	dup2(pipex->pipeline[i - 1][0], 0);
	dup2(pipex->pipeline[i][1], 1);
	ft_close_pipes(pipex);
	execve(pipex->cmds[i][0], pipex->cmds[i], envp);
	perror(pipex->cmds[i][0]);
	ft_pid_exit_with_error();
}

void	ft_wait_pids(pid_t *pids, t_pipex *pipex)
{
	int		last_exit_cmd_status;
	int		i;

	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &last_exit_cmd_status, 0);
		i++;
	}
	if (pipex->here_doc)
		unlink("/tmp/here_doc");
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
	pid_t	*pids;
	int 	i;
	
	pids = ft_alloc_lst(sizeof(pid_t) * pipex->n_cmds + 1, 4);
	ft_pipeline(pipex);
	i = 0;
	while (i < pipex->n_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			ft_exit_fork();//revisar para asegurar espera de forks abiertos y liberar correctamente
		if (pids[i] == 0)
		{
			if (i == 0)
				ft_first_pid(pipex, envp);
			else if (i == pipex->n_cmds - 1)
				ft_last_pid(pipex, i, envp);
			else
				ft_middle_pid(pipex, i, envp);
		}
		i++;
	}
	ft_close_pipes(pipex);
	ft_wait_pids(pids, pipex);
}
