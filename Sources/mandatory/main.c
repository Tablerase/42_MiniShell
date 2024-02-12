/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:28 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/12 16:17:07 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	main(void)
{
	char* 	input;
	t_lexer lexic;

    while(1)
	{
        input = readline(">> ");

        if (!input) {
            break;
        }

        add_history(input);
        printf("You entered: %s\n", input);

		lexer(input, &lexic);
		// TODO: parser (gather syntax tree and handle $variable expansion)
        free(input);
    }
    return 0;
}
