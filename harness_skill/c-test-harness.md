# C test harness (generic only)

Teach mechanics. Do not fill this in with Codexion cases.

A test is a second program with its own `main`. It calls the student’s functions and uses `assert` from `<assert.h>`. Failed `assert` aborts. Success is exit status 0.

Compile the test file together with the student `.c` files under test, not into the `codexion` binary. Keep test sources under `tests/`.

The only code sample allowed from this coach:

```c
#include <assert.h>

int main(void)
{
	assert(2 + 2 == 4);
	return (0);
}
```

Then switch to English for Codexion: what to assert, which argv shape, which log line — never the test body.

Do not show `make` recipes for this project. Say: add a test binary that is not `$(NAME)`.
