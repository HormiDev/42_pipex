/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_forck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:06:29 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/10 03:38:45 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void imprimir_mensaje(const char *mensaje, int veces, int *status) {
    for (int i = 0; i < veces; i++) {
        printf("%s %d ciclo\n", mensaje, status[0]);
		status[0]++;
		sleep(2);
    }
}

int main() {
    pid_t	pid1;
	int		*status;

    pid1 = fork();
	status = (int *)malloc(sizeof(int));
	status[0] = 0;
    if (pid1 < 0 ) {
        fprintf(stderr, "Error al crear el proceso hijo\n");
        return 1;
    } else if (pid1 == 0) {
        // Código del proceso hijo
        imprimir_mensaje("Proceso hijo1", 4, status);
		free(status);
        exit(0); // Terminar el proceso hijo
    } else {
        // Código del proceso padre
		sleep(1);
        imprimir_mensaje("Proceso padre", 3, status);
    }
	wait(NULL);
	free(status);
    return 0;
}
