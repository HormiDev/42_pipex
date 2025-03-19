/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:32:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/19 21:13:39 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	t_list	*file;
	int 	pipe_fd[2];
	char	*line;

	if (argc < 2)
	{
		ft_printf("Usage: %s <limiter>\n", argv[0]);
		return 1;
	}
	
	file = ft_lstnew_ae(ft_strdup_ae(""));
	ft_printf("%s > ", argv[1]);
	line = ft_add_to_alloc_lst_e(get_next_line(0));
	while (line && ft_strncmp_p(line, argv[1], ft_strlen(argv[1])) != 0)
	{
		ft_printf("%s > ", argv[1]);
		ft_lstadd_back(&file, ft_lstnew_ae((line)));
		line = ft_add_to_alloc_lst_e(get_next_line(0));
	}

	pipe(pipe_fd);
	dup2(pipe_fd[0], 0);

	if (fork() == 0)
	{
		dup2(pipe_fd[0], 0);
		line = get_next_line(0);
		while (line)
		{
			sleep(1);
			ft_printf("%s", line);
			free(line);
			line = get_next_line(0);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(0);
	}

	dup2(pipe_fd[1], 1);
	while (file)
	{
		ft_dprintf(pipe_fd[1], "%s", file->content);
		file = file->next;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	ft_alloc_lst(0, 0);
	return 0;
}