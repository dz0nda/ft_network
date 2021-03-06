/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_stralen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 14:25:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:16 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

size_t		ft_stralen(char **array)
{
	size_t	i;

	i = 0;
	if (array)
		while (array[i])
			i++;
	return (i);
}
