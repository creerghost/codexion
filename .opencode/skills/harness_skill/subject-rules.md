# Codexion subject rules (coach reference)

Not a solution. Use to check student work. Never quote these as copy-pasteable source.

## Program

Name: `codexion`. C + 42 Norm. Makefile: `NAME`, `all`, `clean`, `fclean`, `re`. Flags: `-Wall -Wextra -Werror -pthread`. No globals. libft not authorized. Tests need not be submitted.

## Arguments (all mandatory)

`number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler`

Times in milliseconds. `scheduler` is exactly `fifo` or `edf`. Reject negative numbers, non-integers, and any other scheduler.

- **fifo:** grant the dongle to the request that arrived first.
- **edf:** grant to earliest deadline = `last_compile_start + time_to_burnout`. Tie-break must be deterministic (subject requires a rule; student must pick and test one).

## Whitelist (only these from the libc/pthread set)

`pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`, `pthread_cond_init`, `pthread_cond_wait`, `pthread_cond_timedwait`, `pthread_cond_signal`, `pthread_cond_broadcast`, `pthread_cond_destroy`, `gettimeofday`, `clock_gettime`, `usleep`, `write`, `malloc`, `free`, `printf`, `fprintf`, `strcmp`, `strlen`, `atoi`, `memset`

Student may write other functions *they* implement, if those functions only use this list.

## Simulation

One thread per coder. One dongle between each adjacent pair; one coder ⇒ one dongle. Each dongle’s state protected by a mutex; condvar allowed for wait queues.

Compile needs two dongles. After release, a dongle stays unavailable for `dongle_cooldown` ms.

Must implement a heap for FIFO/EDF (no stdlib priority queue).

Separate monitor thread detects burnout; burnout log ≤ 10 ms after the event. Logging serialized (no interleaved lines).

Stop: one burnout, or every coder has compiled ≥ `number_of_compiles_required` times.

## Logs (wording exact)

`timestamp_in_ms X has taken a dongle`  
`timestamp_in_ms X is compiling`  
`timestamp_in_ms X is debugging`  
`timestamp_in_ms X is refactoring`  
`timestamp_in_ms X burned out`

## README (English)

First line italic: `This project has been created as part of the 42 curriculum by <login>…`  
Required sections: Description, Instructions, Resources (including how AI was used), Blocking cases handled, Thread synchronization mechanisms.
