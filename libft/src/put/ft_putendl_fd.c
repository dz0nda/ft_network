/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   putendl_fd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:11:59 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/10 18:55:25 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_put.h"

void	ft_putendl_fd(const char *s, int fd)
{
	if (s)
		ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}