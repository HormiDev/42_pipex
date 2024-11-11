/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:14:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/11 00:58:23 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../42_Libft/libft.h"

typedef struct s_pipex
{
	char	*infile;
	char	***cmds;
	char	*outfile;
	char 	**path_dirs;
	int		pipe_fd[2];
} t_pipex;

t_pipex	*ft_parsing_pipex(int argc, char **argv, char **envp);
void	ft_print_pipex(t_pipex *pipex);

#endif
