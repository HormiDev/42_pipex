/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:57:22 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/16 19:44:54 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_ckeck_cmd(char **cmd, char **path_dirs)
{
	int		i;
	char	*path;

	i = 0;
	while (path_dirs[i])
	{
		path = ft_strjoin_ae(path_dirs[i], "/");
		path = ft_strjoin_ae(path, cmd[0]);
		if (access(path, X_OK) == 0)
		{
			cmd[0] = path;
			return (1);
		}
		i++;
	}
	if (access(cmd[0], X_OK) == 0)
		return (1);
	return (0);
}

void	ft_check_cmds(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmds[i])
	{
		if (!ft_ckeck_cmd(pipex->cmds[i], pipex->path_dirs))
		{
			ft_putstr_fd("\033[0;31mError\n\033[0;33mCommand not found: ", 2);
			ft_putstr_fd(pipex->cmds[i][0], 2);
			ft_putstr_fd("\033[0m\n", 2);
			ft_alloc_lst(0, 0);
			exit(1);
		}
		i++;
	}
}

void	ft_parsing_path(t_pipex *pipex, char **envp)
{
	char	*path;

	while (*envp)
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
	pipex->infile = argv[1];
	pipex->cmds = (char ***)ft_alloc_lst((argc - 3) + 1 * sizeof(char **), 4);
	pipex->n_cmds = argc - 3;
	i_cmd = 2;
	while (i_cmd <= argc - 2)
	{
		pipex->cmds[i_cmd - 2] = ft_split_ae(argv[i_cmd], ' ');
		i_cmd++;
	}
	pipex->outfile = argv[4];
	ft_parsing_path(pipex, envp);
	ft_check_cmds(pipex);
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
