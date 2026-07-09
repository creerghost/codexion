/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dongle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:54:20 by vlnikola          #+#    #+#             */
/*   Updated: 2026/07/08 14:02:20 by vlnikola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*mock_coder_thread(void *arg)
{
	t_coder		*coder;
	t_dongle	*dongle;

	coder = (t_coder *)arg;
	dongle = &coder->ctx->dongles[0];
	ft_sleep(coder->id * 10, coder->ctx);
	printf("Coder %d requesting dongle\n", coder->id);
	if (grab_dongle(coder, dongle))
	{
		printf("Coder %d ACQUIRED dongle\n", coder->id);
		ft_sleep(50, coder->ctx);
		printf("Coder %d releasing dongle\n", coder->id);
		release_dongle(dongle);
	}
	return (NULL);
}

int	main(void)
{
	t_context	ctx;
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;
	static char	*argv[] = {"./codexion", "3", "800", "200", "200", "200", "3",
		"50", "FIFO"};

	if (!init_context(9, argv, &ctx))
		return (1);
	pthread_create(&t1, NULL, mock_coder_thread, &ctx.coders[0]);
	pthread_create(&t2, NULL, mock_coder_thread, &ctx.coders[1]);
	pthread_create(&t3, NULL, mock_coder_thread, &ctx.coders[2]);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	free_context(&ctx);
	return (0);
}
