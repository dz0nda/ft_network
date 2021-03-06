/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:10:21 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:37:52 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_lst.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}
