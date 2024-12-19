/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:57:22 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/12/19 23:46:37 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parsing_cmd(char **cmd, char **path_dirs)
{
	int		i;
	char	*path;

	i = 0;
	while (path_dirs[i])
	{
		path = ft_strjoin_ae(path_dirs[i], "/");
		path = ft_strjoin_ae(path, cmd[0]);
		if (access(path, X_OK) == 0)
			cmd[0] = path;
		i++;
	}
}

void	ft_parsing_cmds(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmds[i])
	{
		ft_parsing_cmd(pipex->cmds[i], pipex->path_dirs);
		i++;
	}
}

void	ft_parsing_path(t_pipex *pipex, char **envp)
{
	char	*path;

	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = *envp + 5;
			break ;
		}
		envp++;
	}
	pipex->path_dirs = ft_split_ae(path, ':');
}

t_pipex	*ft_parsing_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i_cmd;
	int		*fds;

	pipex = (t_pipex *)ft_alloc_lst(sizeof(t_pipex), 4);
	pipex->infile = argv[1];
	pipex->cmds = (char ***)ft_alloc_lst((argc - 3) + 1 * sizeof(char **), 4);
	pipex->n_cmds = argc - 3;
	i_cmd = 2;
	while (i_cmd <= argc - 2)
	{
		if (i_cmd <= argc)
		{
			fds = (int *)ft_alloc_lst(2 * sizeof(int), 4);
			pipe(fds);
			ft_lstadd_back(&pipex->pipes_fds, ft_lstnew_a(fds));
		}
		pipex->cmds[i_cmd - 2] = ft_split_ae(argv[i_cmd], ' ');
		i_cmd++;
	}
	pipex->outfile = argv[4];
	ft_parsing_path(pipex, envp);
	ft_parsing_cmds(pipex);
	return (pipex);
}

void	ft_print_pipex(t_pipex *pipex)
{
	int	i;
	int	j;

	ft_printf("%s ", pipex->infile);
	i = 0;
	while (pipex->cmds[i])
	{
		j = 0;
		while (pipex->cmds[i][j])
		{
			ft_printf("%s ", pipex->cmds[i][j]);
			j++;
		}
		i++;
	}
	ft_printf ("%s\n", pipex->outfile);
	i = 0;
	while (pipex->path_dirs[i])
	{
		ft_printf("%s\n", pipex->path_dirs[i]);
		i++;
	}
}
