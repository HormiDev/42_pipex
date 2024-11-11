/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:46:09 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/05 02:21:47 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *ls = "/bin/ls";

	if (argc < 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return 1;
	}
	execve(ls, argv, 0);
	return 0;
}