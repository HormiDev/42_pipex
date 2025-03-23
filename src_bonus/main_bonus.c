/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:29:55 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/23 17:15:12 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5 || (ft_strncmp_p(argv[1], "here_doc", 9) == 0 && argc < 6))
	{
		ft_putstr_fd("\033[0;31mError\n\033[0;33mUsage: ./pipex infile", 2);
		ft_putstr_fd(" cmd1 cmd2 cmd... outfile\nor\nUsage: ./pipex", 2);
		ft_putstr_fd(" here_doc LIMITER cmd1 cmd2 cmd... outfile\n\033[0m", 2);
		return (1);
	}
	pipex = ft_parsing_pipex(argc, argv, envp);
	ft_executions(pipex, envp);
	ft_alloc_lst(0, 0);
	return (0);
}
