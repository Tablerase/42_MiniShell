/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:58:23 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 18:51:34 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * Exits the current process. The argument is the exit status. If no
 * argument is given, the exit status will be the last executed command.
 * @param exec_struct The structure that contains everything
*/
int	ft_exit(t_exec *exec_struct, t_table *table)
{
	char	**arg;
	int		exit_code;

	arg = table->args;
	if (arg[0] == NULL)
		exit_code = exec_struct->exit_status;
	else if (ft_strnum(arg[0]) == 0 || number_too_big(arg[0]) == 0)
	{
		write(2, "exit :", 6);
		write(2, arg[0], ft_strlen(arg[0]));
		write(2, ": numeric argument required\n", 28);
		exit_code = 2;
	}
	else if (arg[1] != NULL)
	{
		write(2, "exit: too many arguments\n", 25);
		exit_code = 1;
	}
	else
		exit_code = exit_code_exit(arg[0]);
	exec_struct->exit_status = exit_code;
	free_exec_struct(*exec_struct);
	exit(exec_struct->exit_status);
}

/**
 * Checks if the argument given to the exit builtin is valid.
 * On success, returns 1. On failure, returns 0.
 * @param str The argument that is being checked.
*/
int	ft_strnum(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Checks if the argument given to the exit builtin is in the range of a
 * long long int. On success, returns 1. On failure, returns 0.
 * The argument 000012774673 is valid.
 * @param str The number (type string) that is being checked.
*/
int	number_too_big(char *str)
{
	size_t		i;
	size_t		len;

	i = 0;
	while (str[i] == '0')
		i++;
	len = ft_strlen(str) - i;
	if (str[i] == '-')
	{
		if (len > 20)
			return (0);
		if (len == 20 && ft_strcmp(&str[i], "-9223372036854775808") > 0)
			return (0);
	}
	else
	{
		if (len > 19)
			return (0);
		if (len == 19 && ft_strcmp(&str[i], "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

/**
 * Convert the argument passed with the exit builtin into a long long int.
 * @param str The string we are converting.
*/
long long int	ft_atoll(char *str)
{
	int					i;
	int					sign;
	long long			res;
	unsigned long long	number;

	i = 0;
	number = 0;
	while (str[i] == '0')
		i++;
	sign = (str[i] == '-');
	i += sign;
	while (str[i] != '\0')
		number = number * 10 + str[i++] - '0';
	if (sign == 1)
		res = (long long int)(-1 * number);
	else
		res = (long long int)number;
	return (res);
}

/**
 * As the actual exit_code returned is not always the argument passed,
 * we should convert the real value of the exit_code via a modulo.
 * @param str The argument that needs to be converted.
*/
int	exit_code_exit(char *str)
{
	long long	number;

	number = ft_atoll(str);
	if (number >= 0)
		return ((int)(number % 256));
	number = number % 256;
	return ((int)((number + 256) % 256));
}

// Should display exit if main process such as with CTRL-D
// max for exit 9223372036854775807