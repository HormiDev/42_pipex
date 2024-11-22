/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 03:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/22 01:17:53 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"

int	main(void)
{
	int	pipe_fd[2];
	int prev_pipe_fd;
	int infile_fd;
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;

	infile_fd = open("/dev/urandom", O_RDONLY);
	prev_pipe_fd = -1;
	pipe(pipe_fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(infile_fd, 0);
		close(infile_fd);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		execve("/bin/head", (char *[]){"head", "-c", "100", NULL}, NULL);
		exit(127);
	}
	close(prev_pipe_fd);
	close(pipe_fd[1]);
	prev_pipe_fd = pipe_fd[0];
	pipe(pipe_fd);

	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		execve("/bin/cat", (char *[]){"cat", NULL}, NULL);
		exit(127);
	}
	pid3 = fork();
	if (pid3 == 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		pipe_fd[1] = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		execve("/bin/head", (char *[]){"head", NULL}, NULL);
		exit(127);
	}
	waitpid(pid3, 0, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(0);
	wait(0);
	return (0);
}