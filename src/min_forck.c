/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_forck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:12:29 by ide-dieg          #+#    #+#             */
/*   Updated: 2024/11/05 18:34:50 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void imprimir_mensaje(const char *mensaje, int veces) {
    for (int i = 0; i < veces; i++) {
        printf("%s %d\n", mensaje, i + 1);
    }
}

int main() {
    pid_t pid1;
	pid_t pid2;

    pid1 = fork();
	pid2 = fork();

    if (pid1 < 0 ) {
        fprintf(stderr, "Error al crear el proceso hijo\n");
        return 1;
    } else if (pid1 == 0) {
        // Código del proceso hijo
        imprimir_mensaje("Proceso hijo1", 1000);
        exit(0); // Terminar el proceso hijo
    } else {
        // Código del proceso padre
        imprimir_mensaje("Proceso padre", 1);
    }
	if (pid2 < 0 ) {
		fprintf(stderr, "Error al crear el proceso hijo\n");
		return 1;
	} else if (pid2 == 0) {
		// Código del proceso hijo
		imprimir_mensaje("Proceso hijo2", 1000);
		exit(0); // Terminar el proceso hijo
	} else {
		// Código del proceso padre
		imprimir_mensaje("Proceso padre", 1);
		
	}
	wait(NULL);
    return 0;
}
