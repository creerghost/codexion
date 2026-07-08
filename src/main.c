#include "codexion.h"

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (!init_context(argc, argv, &ctx))
		return (1);
	
	printf("Initialized %d coders and %d dongles\n", ctx.args->num_coders, ctx.args->num_coders);
	
	free_context(&ctx);
	return (0);
}
