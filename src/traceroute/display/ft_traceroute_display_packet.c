/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_display_packet.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/27 17:52:33 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

tvsub(t_timeval *out, t_timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) < 0)   {
		out->tv_sec--;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}

int ft_tr_resolve(t_sockaddr_in *from, char *name)
{
    struct sockaddr_in sa;    /* input */
    socklen_t len;         /* input */
    char hbuf[NI_MAXHOST];

    memset(&sa, 0, sizeof(struct sockaddr_in));

    char *s = NULL;

    /* For IPv4*/
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(inet_ntoa(from->sin_addr));
    len = sizeof(struct sockaddr_in);

    if (getnameinfo((struct sockaddr *) &sa, len, hbuf, sizeof(hbuf), 
        NULL, 0, NI_NAMEREQD)) {
        // printf("could not resolve hostname\n");
        // s = malloc(sizeof(NI_MAXHOST));
        ft_strcpy(name, inet_ntoa(from->sin_addr));

    }
    else {
        // printf("host=%s\n", hbuf);
        // s = malloc(sizeof(NI_MAXHOST));
        ft_strcpy(name, hbuf);
    }

    return 0;
}

int   ft_traceroute_print(t_trace *ctx, int cc)
{
  char str[FT_ADDRSTRLEN];
  char str2[FT_ADDRSTRLEN];
  char *tmp = inet_ntoa(ctx->from.saddrin.sin_addr);
  ft_strcpy(str, tmp);
  // tmp = inet_ntoa(ctx->from.saddrin.sin_addr);
  // ft_strcpy(str2, tmp);

    t_timeval tv;
    t_timeval res;

    gettimeofday(&tv, NULL);
    
    // timersub(&tv, &ctx->time.start, &res);

    // printf("took %lu us\n", (tv.tv_sec - ctx->time.start.tv_sec) * 1000000 + tv.tv_usec - ctx->time.start.tv_usec); 

    // tvsub(&tv, &ctx->time.start);
	  // int dt = tv.tv_sec*1000 + (tv.tv_usec + 500)/1000;

  // double dt = (double)(tv.tv_usec - ctx->time.start.tv_usec) / 1000 + (double)(tv.tv_sec - ctx->time.start.tv_sec);
  
  double start = (ctx->time.start.tv_sec) * 1000 + (ctx->time.start.tv_usec) / 1000;
  double stop = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;

  // long long start = ctx->time.start.tv_sec*1000LL + ctx->time.start.tv_usec/1000; // calculate milliseconds
  // long long stop = tv.tv_sec*1000LL + tv.tv_usec/1000; // calculate milliseconds
  // printf(" %ld %ld", start, stop);

  double dt = stop - start;

  // long long dt = stop - start;

  // if (!ft_strequal(str, ctx->last_addr)) {
  //   // ft_memcpy(&ctx->from.saddrin, from, sizeof(ctx->from.saddrin));

  //   ft_strcpy(ctx->last_addr, str);
  //   // struct hostent *he;

  //   // he = gethostbyaddr(inet_ntoa(ctx->from.saddrin.sin_addr), sizeof(from), 0);
  //   char name[NI_MAXHOST];
  //   ft_tr_resolve(&ctx->from.saddrin, name);

  //   printf(" %d  %s (%s)", ttl, name, ctx->last_addr);
  // }
  
  if (ctx->opts.probes == 0)
    printf(" %d", ctx->opts.hops);

  if (!ft_strequal(ctx->from.ip_last, str)) {
    ft_strcpy(ctx->from.ip_last, str);

    char name[NI_MAXHOST];
    ft_tr_resolve(&ctx->from.saddrin, name);

    printf("  %s (%s)", name, ctx->from.ip_last);
  }

  if (cc == 0) {
    printf("  *");
  } else {
    printf("  %0.2f ms", dt);
  }

  return (EXIT_SUCCESS);
}
