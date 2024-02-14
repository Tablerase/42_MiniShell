/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:28 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/14 12:46:26 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_shell_init(t_shell *shell, char **envp)
{
	shell->table_head = NULL;
	shell->env = ft_strs_dup(envp);
}

int	main(int ac, char **av, char **envp)
{
	// char* 		input;
	t_shell 	shell;
	// t_lexer 	lexic;

	(void)ac;
	(void)av;
	(void)envp;
	ft_shell_init(&shell, envp);
	
	printf("Shell env: %s\n", shell.env[0]);
	ft_free_all(&shell);
    // while(1)
	// {
    //     input = readline(">> ");

    //     if (!input) {
    //         break;
    //     }

    //     add_history(input);
    //     printf("You entered: %s\n", input);

	// 	if (lexer(input, &lexic) == true)
	// 	{
	// 		print_tokens(lexic.head);
	// 		parser(&lexic, &shell.table_head, &shell.env);
	// 		free_tokens(lexic.head);
	// 	}
    //     free(input);
    // }
    // return 0;
}
