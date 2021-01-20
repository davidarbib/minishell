/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:06:13 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/20 16:06:13 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	print_tokens_acc(t_list *tokens, int first)
{
	if (!tokens)
	{
		write(1, "]", 1);
		return ;
	}
	if (first)
		write(1, "[", 1);
	else
		write(1, ", ", 1);
	/*write(1, ((t_token*)tokens->content)->str,*/
			/*((t_token*)tokens->content)->len);*/
	write(1, tokens->content, 1);
	print_tokens_acc(tokens->next, 0);
}

void	print_tokens(t_list *tokens)
{
	print_tokens_acc(tokens, 1);
}

void	eval(t_list *command)
{
	char	**tab;
	int		size;

	tab = (char**)ft_lsttotab(command, 8, &size);
	/*char **rest = tab + 8;*/
	printf("%d\n", size);
	//tab[size] = 0;
	printf("-%s-\n", (char*)tab[0]);
	/*execve((char*)tab, rest, NULL);*/
	/*printf("%d\n", size);*/
	/*int size;*/

	/*tab = ft_lsttotab(list, 8, &size);*/
	/*printf("%p\n", tab);*/
	/*for (int i = 0; i < size; i++)*/
	/*{*/
		/*printf("%s\n", (char*)(tab + i));*/
	/*}*/
	/*execve(tab[0], tab + 8, NULL);*/
}

int main ()
{
	t_list	*list = ft_lstnew("/bin/lsurieqopuiewqouioqurioqwep");
	t_list	*list2 = ft_lstnew(ft_strdup("-a"));
	t_list	*list3 = ft_lstnew(ft_strdup("-l"));
	ft_lstadd_back(&list, list2);
	ft_lstadd_back(&list, list3);

	eval(list);
	/*printf("length = %d\n", ft_lstsize(list));*/

	/*printf("size = %d\n", number);*/
	/*for (int i = 0; i < 16; i += 8)*/
		/*printf("\"%s\"\n", *(toto + i));*/
}
