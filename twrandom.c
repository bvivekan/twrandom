#include <stdio.h>
#include <stdlib.h>

#define PERFORMANCE 1

static struct random_state {
	unsigned int s1;
	unsigned int s2;
	unsigned int s3;
	unsigned int s4;
} state;


/**
 *	prandom_u32_state - seeded pseudo-random number generator.
 *	@state: pointer to state structure holding seeded state.
 */
unsigned int prandom_u32_state(void)
{
#define TAUSWORTHE(s, a, b, c, d) ((s & c) << d) ^ (((s << a) ^ s) >> b)
	state.s1 = TAUSWORTHE(state.s1,  6U, 13U, 4294967294U, 18U);
	state.s2 = TAUSWORTHE(state.s2,  2U, 27U, 4294967288U,  2U);
	state.s3 = TAUSWORTHE(state.s3, 13U, 21U, 4294967280U,  7U);
	state.s4 = TAUSWORTHE(state.s4,  3U, 12U, 4294967168U, 13U);

	return (state.s1 ^ state.s2 ^ state.s3 ^ state.s4);
}

int main(int argc, char **argv)
{
	unsigned int count = 1;
	unsigned int i = 0;

	if (argc < 5) {
		printf("Usage: %s seed1 seed2 seed3 seed4\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	state.s1 = atoi(argv[1]);
	state.s2 = atoi(argv[2]);
	state.s3 = atoi(argv[3]);
	state.s4 = atoi(argv[4]);

	if (argc > 5)
		count = atoi(argv[5]);

	printf("Status: s1:%u, s2:%u, s3:%u, s4:%u, count:%u\n",
			state.s1, state.s2, state.s3, state.s4, count);

	while (i < count) {
		if (PERFORMANCE == 0)
			printf("[%u].Random number: %u\n", i, prandom_u32_state());
		else
			prandom_u32_state();
		i++;
	}
}
