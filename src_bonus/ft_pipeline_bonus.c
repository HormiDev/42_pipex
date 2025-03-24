/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 04:39:25 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/24 03:17:59 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->pipeline[i])
	{
		close(pipex->pipeline[i][0]);
		close(pipex->pipeline[i][1]);
		i++;
	}
}

void	ft_pipeline(t_pipex *pipex)
{
	int	i;

	pipex->pipeline = ft_alloc_lst(sizeof(int *) * (pipex->n_cmds + 1), 4);
	i = 0;
	while (i < pipex->n_cmds - 1)
	{
		pipex->pipeline[i] = ft_alloc_lst(sizeof(int) * 2, 4);
		if (pipe(pipex->pipeline[i]) == -1)
		{
			ft_close_pipes(pipex);
			ft_exit_pipe();
		}
		i++;
	}
}
