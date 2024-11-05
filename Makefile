# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 21:33:00 by ide-dieg          #+#    #+#              #
#    Updated: 2024/11/04 21:42:22 by ide-dieg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

update_submodules:
	@echo "Updating submodules..."
	@git submodule update --init --recursive > /dev/null 2>&1
	@tput cuu1 && tput el
	@echo "Submodules updated."
