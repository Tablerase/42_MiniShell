/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:52:47 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/14 12:46:51 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// Array of strings

int		ft_strs_len(char **strs);
char	**ft_strs_dup(char **strs);
void	ft_free_strs(char **strs);

// Free all

void	ft_free_all(t_shell *shell);

#endif