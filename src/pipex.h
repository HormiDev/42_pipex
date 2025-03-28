/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:14:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/23 12:49:53 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "../42_Libft/libft.h"

typedef struct s_pipex
{
	char	*infile;
	int		n_cmds;
	char	***cmds;
	char	*outfile;
	char	**path_dirs;
	int		pipe_fd[2];
}	t_pipex;

void	ft_executions(t_pipex *pipex, char **envp);
t_pipex	*ft_parsing_pipex(int argc, char **argv, char **envp);
void	ft_print_pipex(t_pipex *pipex);
void	ft_closefiles(t_pipex *pipex);
char	**ft_split_quotes(char *str);
void	ft_pid_exit_with_error(void);
void	ft_exit_fork(void);
void	ft_exit_pipe(void);

#endif
