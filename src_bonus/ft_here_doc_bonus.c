/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:11:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/19 20:28:58 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_read_here_doc(char *limiter, t_list **here_doc)
{
	char	*line;

	*here_doc = ft_lstnew_ae(ft_strdup_ae(""));
	line = ft_add_to_alloc_lst_e(get_next_line(0));
	while (line && ft_strncmp_p(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		ft_printf("%s > ", limiter);
		ft_lstadd_back(here_doc, ft_lstnew_ae((line)));
		line = ft_add_to_alloc_lst_e(get_next_line(0));
	}
}