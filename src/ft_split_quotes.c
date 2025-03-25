/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:20:45 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/25 11:42:29 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_delete_quotes(t_list *lst)
{
	char	*str;
	int		qoutes;

	while (lst)
	{
		str = (char *)lst->content;
		qoutes = 0;
		while (*str)
		{
			*(str - qoutes) = *str;
			if (*str == '\'' || *str == '\"')
				qoutes++;
			str++;
		}
		*(str - qoutes) = '\0';
		lst = lst->next;
	}
}

static char	**ft_clen_and_transform(t_list *lst)
{
	char	**ret;
	int		i;

	ft_delete_quotes(lst);
	ret = ft_alloc_lst(sizeof(char *) * (ft_lstsize(lst) + 1), 2);
	i = 0;
	while (lst)
	{
		ret[i] = lst->content;
		lst = lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static void	ft_jump_quotes(char *str, int *i)
{
	char	qoute;

	qoute = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != qoute)
		(*i)++;
}

char	**ft_split_quotes(char *str)
{
	t_list	*lst;
	int		i;

	lst = NULL;
	if (!*str)
		ft_lstadd_back(&lst, ft_lstnew_ae(ft_strdup_ae("")));
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
		{
			i = 0;
			while (str[i] && str[i] != ' ' && str[i] != '\t')
			{
				if (str[i] == '\'' || str[i] == '\"')
					ft_jump_quotes(str, &i);
				if (str[i])
					i++;
			}
			ft_lstadd_back(&lst, ft_lstnew_ae(ft_substr_ae(str, 0, i)));
			str += i;
		}
		if (*str)
			str++;
	}
	return (ft_clen_and_transform(lst));
}
/*
int main(int argc, char **argv)
{
	char	**ret;
	int		i;

	if (argc != 2)
		return (1);
	ret = ft_split_quotes(argv[1]);
	i = 0;
	while (ret[i])
	{
		printf("%s\n", ret[i]);
		i++;
	}
	ft_alloc_lst(0, 0);
	return (0);
}*/
