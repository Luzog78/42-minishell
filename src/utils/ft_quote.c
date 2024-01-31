/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:37:18 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/01 00:42:06 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*Faire une fonction qui renvoie un char * qui a été malloc
 *Avec les ",',$ avec getenv pour $
 *La premiere quote est connecte a la quote la plus proche
 *Ex: '"""'$PWD'"""' -> """/nfs/home/..."""
*/
