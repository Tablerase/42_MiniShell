/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:40:48 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/19 17:57:28 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <string.h>

int	ft_strlen(char *str);

int	main(void)
 {
	char	test[] = "ZAFDafdsfafdafaadfjskajdshfk\njadhsfkjahdskjfhasdkjf";
	char	test2[] = "AFDA";
	char	test3[] = "";

	printf("\e[0;32mTEST:\e[0m %s|%i|%li", 
	test, ft_strlen(test), strlen(test));
	printf("\n\e[0;32mTEST:\e[0m %s|%i|%li", 
	test2, ft_strlen(test2), strlen(test2));
	printf("\n\e[0;32mTEST:\e[0m %s|%i|%li", 
	test3, ft_strlen(test3), strlen(test3));

	return 0;
}
*/

#include "../Includes/libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
