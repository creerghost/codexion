#include "codexion.h"

int main(int argc, char **argv)
{
	t_context ctx;
	t_args args;

	ctx.args = &args;
	return (!parse_args(argc, argv, &ctx));
}
