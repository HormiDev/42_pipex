/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pipex_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:57:22 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/23 19:22:50 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parsing_cmd(char **cmd, char **path_dirs)
{
	int		i;
	char	*path;

	i = 0;
	if (path_dirs == NULL)
		return ;
	while (path_dirs[i])
	{
		path = ft_strjoin_ae(path_dirs[i], "/");
		path = ft_strjoin_ae(path, cmd[0]);
		if (access(path, X_OK) == 0)
		{
			cmd[0] = path;
			return ;
		}
		i++;
	}
}

void	ft_parsing_cmds(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmds[i])
	{
		if (ft_strchr(pipex->cmds[i][0], '/') == NULL)
			ft_parsing_cmd(pipex->cmds[i], pipex->path_dirs);
		i++;
	}
}

void	ft_parsing_path(t_pipex *pipex, char **envp)
{
	char	*path;

	path = NULL;
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

	pipex = (t_pipex *)ft_alloc_lst(sizeof(t_pipex), 4);
	if (ft_strncmp_p(argv[1], "here_doc", 9) == 0)
	{	
		pipex->here_doc = 1;
		ft_here_doc(argv[2]);
		pipex->infile = "/tmp/here_doc";
		pipex->cmds = (char ***)ft_alloc_lst((argc - 4 + 1) * sizeof(char **), 4);
		pipex->n_cmds = argc - 4;
		i_cmd = 3;
		while (i_cmd <= argc - 2)
		{
			pipex->cmds[i_cmd - 3] = ft_split_quotes(argv[i_cmd]);
			i_cmd++;
		}
		pipex->outfile = argv[argc - 1];
	}
	else
	{
		pipex->infile = argv[1];
		pipex->cmds = (char ***)ft_alloc_lst((argc - 3 + 1) * sizeof(char **), 4);
		pipex->n_cmds = argc - 3;
		i_cmd = 2;
		while (i_cmd <= argc - 2)
		{
			pipex->cmds[i_cmd - 2] = ft_split_quotes(argv[i_cmd]);
			i_cmd++;
		}
		pipex->outfile = argv[argc - 1];
	}
	ft_parsing_path(pipex, envp);
	ft_parsing_cmds(pipex);
	return (pipex);
}

void	ft_print_pipex(t_pipex *pipex) // borrable
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
