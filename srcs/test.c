/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:06:13 by fyusuf-a          #+#    #+#             */
/*   Updated: 2021/01/25 14:49:43 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

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

void	del(void* vd)
{
	(void)vd;
}

void	eval(t_list **command)
{
	char	**tab;
	int		size;

	tab = (char**)ft_lsttotab(*command, 8, &size);
	ft_lstclear(command, del);
	tab[size] = 0;
	printf("size = %d\n", size);
	for (int i = 0; i < size; i++)
		printf("mimi: %s\n", tab[i]);
	if (execve((char*)tab[0], (char*const*)tab, NULL) == -1)
		perror("minishell");
}

int	main()
{
	int	pid;
	int	ret_wait;
	int	status;

	t_list	*list = ft_lstnew("/bin/ls");
	t_list	*list2 = ft_lstnew("caca");
	t_list	*list3 = ft_lstnew("-l");
	t_list	*list4 = ft_lstnew("-a");
	ft_lstadd_back(&list, list2);
	ft_lstadd_back(&list, list3);
	ft_lstadd_back(&list, list4);

	pid = fork();
	status = 0;
	if (pid == 0)
	{
		eval(&list);
		return (0);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		while (1)
		{
			if ((ret_wait = waitpid(-1, &status, WUNTRACED)) == -1)
			{
				perror("minishell"); // Voir si EINTR est une erreur qui peut avoir lieu ou pas
				continue;
			}
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break ;
		}
	}
	return (0);
}
