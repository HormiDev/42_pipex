/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_autokill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 04:11:03 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/14 04:12:15 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid = getpid();
	printf("Sending SIGKILL to process %d\n", pid);
	kill(pid, SIGKILL);
	return 0;
}