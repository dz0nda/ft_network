/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_socket_send.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/26 11:44:09 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int   ft_traceroute_socket_send_init(t_trace *ctx)
{
  const int on = 1;
  t_addrinfo  *rp;
  
  rp = ctx->host.result;
	while (rp != NULL) {
		ctx->sock.udp = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (ctx->sock.udp != INVALID_SOCKET)
			break;
		rp = rp->ai_next;
	}

	if (rp == NULL)
		return (EXIT_FAILURE);

	ft_memcpy(&ctx->host.to, rp->ai_addr, sizeof(rp->ai_addr));
	ft_memcpy(ctx->host.ip, inet_ntoa(ctx->host.to.sin_addr), FT_ADDRSTRLEN);

	free(ctx->host.result);

  if (setsockopt (ctx->sock.udp, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
		return (EXIT_FAILURE);

  return (EXIT_SUCCESS);
}

int   ft_traceroute_socket_send(t_trace *ctx)
{
  ft_traceroute_packet_set_header(ctx);

  gettimeofday(&ctx->tv, NULL);

  int i = 0;
  if ((i = sendto(ctx->sock.udp, ctx->sock.data,
                    ctx->opts.packetlen, 0, (t_sockaddr *)&ctx->host.to,
                    sizeof(t_sockaddr))) < 0)
		ft_exit("sendto()");

  return (EXIT_SUCCESS);
}
