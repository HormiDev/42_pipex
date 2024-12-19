/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:29:55 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/12/19 21:36:01 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5)
	{
		ft_putstr_fd("\033[0;31mError\n\033[0;33mUsage: ./pipex", 2);
		ft_putstr_fd(" infile cmd1 cmd2 outfile\n\033[0m", 2);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) != 0 && argc < 6)
	{
		ft_putstr_fd("\033[0;31mError\n\033[0;33mUsage: ./pipex", 2);
		ft_putstr_fd(" here_doc LIMITER cmd1 cmd2 outfile\n\033[0m", 2);
		return (1);
	}
	pipex = ft_parsing_pipex(argc, argv, envp);
	ft_executions(pipex, envp);
	ft_alloc_lst(0, 0);
	return (0);
}
