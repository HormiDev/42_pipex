/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 00:46:02 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/05 00:52:32 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (access(argv[1], F_OK) == 0)
			printf("File exists\n");
		else
			printf("File does not exist\n");
		if (access(argv[1], R_OK) == 0)
			printf("File is readable\n");
		else
			printf("File is not readable\n");
		if (access(argv[1], W_OK) == 0)
			printf("File is writable\n");
		else
			printf("File is not writable\n");
		if (access(argv[1], X_OK) == 0)
			printf("File is executable\n");
		else
			printf("File is not executable\n");
	}
	return 0;
}