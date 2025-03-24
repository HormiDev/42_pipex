/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:14:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/24 03:02:25 by ide-dieg         ###   ########.fr       */
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
	int		**pipeline;
	int		here_doc;
}	t_pipex;

void	ft_executions(t_pipex *pipex, char **envp);
t_pipex	*ft_parsing_pipex(int argc, char **argv, char **envp);
void	ft_print_pipex(t_pipex *pipex);
void	ft_closefiles(t_pipex *pipex);
char	**ft_split_quotes(char *str);
void	ft_pid_exit_with_error(void);
void	ft_exit_fork(pid_t *pids, t_pipex *pipex);
void	ft_exit_pipe(void);
void	ft_here_doc(char *limiter);
void	ft_pipeline(t_pipex *pipex);
void	ft_close_pipes(t_pipex *pipex);
void	ft_exit_command_not_found(t_pipex *pipex, int i);

#endif
