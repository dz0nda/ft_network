/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/06 13:17:47 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int probes_max = 3;
int hops_max = 30;
int byte_packets = 60;
int port = 33435;

// int 		ft_tr_exec_probes(t_trace *ctx, int hops)
// {
// 	int probes;
// 	int cc;

// 	probes = 0;
// 	cc = 0;
// 	while (probes < probes_max) {
// 		ft_traceroute_send(ctx, port + hops, hops);
// 		if ((cc = ft_traceroute_receive(ctx, hops))) {
// 			ft_traceroute_print(ctx, hops, probes);
// 			// break;
// 		} else {
// 			printf(" *");
// 		}
// 		probes++;
// 	}
// 	return (EXIT_SUCCESS);
// }

int 		ft_traceroute_exec(t_trace *ctx)
{
	int hops;
	int probes;
	int cc;

	hops = 1;
	while (ctx->args.hops <= ctx->args.hops_max) {
		ctx->args.probes = 0;
		while (ctx->args.probes < ctx->args.probes_max) {
			ft_traceroute_send(ctx);
			cc = ft_traceroute_receive(ctx);
			ft_traceroute_print(ctx, cc);

			ctx->args.probes++;
		}
		
		printf("\n");

		if (ft_strequal(ctx->host.ip, inet_ntoa(ctx->from.sin_addr)))
			break;

		ctx->args.hops++;
	}

	return (EXIT_SUCCESS);
}

static int ft_traceroute_parse(t_trace *ctx, int argc, const char *argv[])
{
	while (argv[ctx->argi] && *argv[ctx->argi] == '-') {
		if (ft_traceroute_args(ctx, argc, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ctx->argi += 2;
	}
	return (EXIT_SUCCESS);
}

int			ft_traceroute(int argc, const char *argv[])
{
	t_trace	ctx;

	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.argi = 1;

	if (argv[1] == NULL || ft_strequal(argv[1], "-h"))
		return (ft_traceroute_help((char *)argv[0]));

	if (ft_traceroute_init(&ctx, argv[1]) == EXIT_FAILURE)
		ft_exit("traceroute_init()");

	if (ft_traceroute_parse(&ctx, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
	// 	ctx.host_name, ctx.host_ipv4, ctx.hops, ctx.byte_packets);
	// ft_traceroute_exec(&ctx);

	close(ctx.sock.udp);
	close(ctx.sock.icmp);

	return (EXIT_SUCCESS);
}
