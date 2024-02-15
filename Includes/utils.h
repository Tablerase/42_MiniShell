/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:52:47 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/15 18:52:12 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// Array of strings

int		ft_strs_len(char **strs);
char	**ft_strs_dup(char **strs);
void	ft_free_strs(char **strs);

// List of commands

void	ft_free_cmds(t_table *head);
void	ft_free_infds(t_inf *head);
void	ft_free_outfds(t_outf *head);

// Free all

void	ft_free_all(t_shell *shell);

#endif