# Codexion — Implementation Plan

A multi-threaded simulation of coders competing for shared USB dongles, modeled after the dining philosophers problem. Each coder is a thread that cycles through **compile → debug → refactor**, needing two dongles (left + right) to compile.

---

## Concepts to Learn First

Before coding, these are the core topics you need to understand:

| Topic | Why It Matters | Key Functions |
|---|---|---|
| **POSIX Threads** | Each coder = 1 thread | `pthread_create`, `pthread_join` |
| **Mutexes** | Protect shared state (dongles, logs, sim flags) | `pthread_mutex_init/lock/unlock/destroy` |
| **Condition Variables** | Coders wait for dongles without busy-looping | `pthread_cond_init/wait/timedwait/broadcast/destroy` |
| **Dining Philosophers** | This project IS the dining philosophers problem | Resource ordering to prevent deadlock |
| **Min-Heap (Priority Queue)** | Required by subject for FIFO/EDF scheduling | Array-based binary heap |
| **gettimeofday** | All timestamps in ms since simulation start | `gettimeofday()` → convert to ms |
| **FIFO vs EDF Scheduling** | Two arbitration policies for dongle access | FIFO = insertion order, EDF = earliest deadline |

> [!IMPORTANT]
> The PDF **explicitly requires** a heap-based priority queue — you cannot use a linked list or array scan for scheduling.

---

## Hard Constraints from the PDF

These are non-negotiable rules that the implementation must respect:

### Compilation & Structure
- All source files in `coders/` directory
- Compile with `-Wall -Wextra -Werror -pthread`
- **No global variables**
- **No memory leaks** (all heap memory freed)
- Makefile rules: `$(NAME)`, `all`, `clean`, `fclean`, `re` ✅ (already done)

### 42 Norm
- Max **25 lines** per function (excluding braces)
- Max **4 parameters** per function
- Max **5 functions** per `.c` file
- Max **5 variable declarations** per function, all at the top
- No `for` loops — use `while` only
- No ternary `?:` operators
- No variable-length arrays (VLA)
- Function prototypes and structs in `.h` files only
- Headers must have include guards

### Threading & Synchronization
- Each coder = **one thread** (`pthread_create`)
- Each dongle protected by **one mutex** (`pthread_mutex_t`)
- Condition variables (`pthread_cond_t`) for wait queues
- **Serialized logging** — a mutex protects all output so lines never interleave
- A **separate monitor thread** detects burnout and stops simulation

### Dongle Rules
- N coders → N dongles (circular arrangement)
- 1 coder → 1 dongle only
- Compiling requires **two dongles** (left + right)
- **Dongle cooldown**: after release, dongle is locked for `dongle_cooldown` ms
- **Fair arbitration**: per-dongle priority queue, either FIFO or EDF

### Scheduling
- **FIFO**: grant dongle to the coder whose request arrived first
- **EDF**: grant dongle to the coder with the earliest burnout deadline (`last_compile_start + time_to_burnout`)
- Must guarantee **liveness** (no starvation) under EDF with feasible parameters

### Timing & Logging
- Burnout log printed **within 10 ms** of actual burnout
- Log format: `timestamp_in_ms X has taken a dongle` / `is compiling` / `is debugging` / `is refactoring` / `burned out`
- Use `gettimeofday()` for real-time measurements

### Simulation End Conditions
- A coder burns out → print burnout, stop all threads
- All coders compiled ≥ `number_of_compiles_required` times → stop

### Allowed Functions (exhaustive)
```
pthread_create, pthread_join,
pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy,
pthread_cond_init, pthread_cond_wait, pthread_cond_timedwait, pthread_cond_broadcast, pthread_cond_destroy,
gettimeofday, usleep, write, malloc, free,
printf, fprintf, strcmp, strlen, atoi, memset
```

> [!CAUTION]
> No `pthread_detach`, no `clock_gettime`, no `nanosleep`, no `exit`. Only the functions listed above.

---

## Architecture — Data Structures

### `t_heap` — Min-Heap Priority Queue
```c
typedef struct s_heap
{
    int     *coder_ids;   // coder IDs stored in the heap
    long    *keys;        // priority key per entry (timestamp for FIFO, deadline for EDF)
    int     size;         // current number of elements
    int     capacity;     // max elements (= number_of_coders)
}   t_heap;
```
- Standard array-based binary min-heap
- `heap_push()`, `heap_pop()`, `heap_peek()` operations
- Key comparison: lower key = higher priority

### `t_dongle` — Shared Resource
```c
typedef struct s_dongle
{
    pthread_mutex_t mutex;        // protects this dongle's state
    pthread_cond_t  cond;         // coders wait here for this dongle
    int             held;         // 1 if currently held, 0 if free
    long            release_time; // timestamp when last released (for cooldown)
    t_heap          wait_queue;   // pending requests sorted by scheduler policy
}   t_dongle;
```

### `t_coder` — Per-Thread Data
```c
typedef struct s_coder
{
    int             id;                  // 1-indexed (for display)
    int             compile_count;       // how many times compiled so far
    long            last_compile_start;  // timestamp of last compile start (0 = sim start)
    int             left_dongle;         // index into sim->dongles
    int             right_dongle;        // index into sim->dongles
    int             first_dongle;        // min(left, right) — acquire first (deadlock prevention)
    int             second_dongle;       // max(left, right) — acquire second
    pthread_t       thread;
    struct s_sim    *sim;                // back-pointer to simulation
}   t_coder;
```

### `t_sim` — Simulation State (passed to all threads)
```c
typedef struct s_sim
{
    int             num_coders;
    long            time_to_burnout;
    long            time_to_compile;
    long            time_to_debug;
    long            time_to_refactor;
    int             num_compiles_req;
    long            dongle_cooldown;
    int             scheduler;           // SCHED_FIFO or SCHED_EDF enum
    long            start_time;          // gettimeofday at sim start
    int             sim_over;            // flag: burnout or all done
    int             all_done;            // flag: all coders finished
    pthread_mutex_t sim_mutex;           // protects sim_over, all_done
    pthread_mutex_t log_mutex;           // serializes all output
    t_dongle        *dongles;            // array[num_coders]
    t_coder         *coders;             // array[num_coders]
}   t_sim;
```

---

## Architecture — File Layout

All files in `coders/`:

### [NEW] [codexion.h](file:///home/nikolaev/codexion_v2/coders/codexion.h)
Main header — all struct definitions, enums, function prototypes, includes.

### [MODIFY] [main.c](file:///home/nikolaev/codexion_v2/coders/main.c)
- Parse & validate all 8 arguments
- Reject negative numbers, non-integers, invalid scheduler
- Call `init_sim()` → launch threads → `pthread_join` all → cleanup

### [NEW] init.c
- `init_sim()` — allocate and initialize `t_sim`, `t_dongle[]`, `t_coder[]`
- Init all mutexes, condvars, heaps
- Assign left/right dongle indices per coder (circular, with resource ordering)

### [NEW] heap.c
- `heap_init()`, `heap_push()`, `heap_pop()`, `heap_peek()`, `heap_destroy()`
- Array-based binary min-heap
- Used by both FIFO (key = request arrival timestamp) and EDF (key = deadline)

### [NEW] dongle.c
- `dongle_acquire(coder, dongle_index)` — add to wait queue, wait on condvar, respect cooldown
- `dongle_release(coder, dongle_index)` — mark free, set release_time, broadcast
- Core scheduling logic lives here

### [NEW] coder.c
- `coder_routine(void *arg)` — the thread function
- Loop: acquire 2 dongles → compile → release dongles → debug → refactor → repeat
- Check `sim_over` before each action
- **Edge case — 1 coder**: only 1 dongle exists but 2 are needed to compile. The coder can never compile → immediate burnout (same as dining philosophers with 1 philosopher and 1 fork). The coder thread should detect it cannot acquire a second dongle and simply wait until the monitor detects burnout.

### [NEW] monitor.c
- `monitor_routine(void *arg)` — separate thread
- Tight polling loop: check all coders' `last_compile_start + time_to_burnout` against current time
- If any coder's deadline has passed → set `sim_over`, print burnout, return
- Also check if all coders reached `num_compiles_req` → set `sim_over` + `all_done`
- Use short `usleep()` intervals (~1ms) to stay within 10ms detection window

### [NEW] logging.c
- `log_msg(t_sim *sim, int coder_id, char *msg)` — lock `log_mutex`, check `sim_over`, print, unlock
- Ensures no interleaving

### [NEW] time_utils.c
- `get_time_ms()` — wrapper around `gettimeofday()`, returns current time in ms
- `elapsed_ms(t_sim *sim)` — returns ms since simulation start
- `ft_sleep(long ms, t_sim *sim)` — precise sleep using `usleep()` + busy-wait tail, checking `sim_over` periodically

### [NEW] cleanup.c
- `cleanup_sim(t_sim *sim)` — destroy all mutexes, condvars, free all heap arrays, free dongles/coders arrays

---

## Key Design Decisions

### Deadlock Prevention — Resource Ordering
The circular dongle layout is the classic dining philosophers deadlock scenario. Solution: **always acquire the lower-indexed dongle first**.

```
Coder i (0-indexed):
  left_dongle  = i
  right_dongle = (i + 1) % N
  first_dongle = min(left, right)    ← acquire this first
  second_dongle = max(left, right)   ← acquire this second
```

This breaks the circular-wait condition (Coffman condition #4).

### Dongle Acquisition Protocol
```
acquire_dongle(coder, dongle_idx):
    1. lock dongle.mutex
    2. compute my priority key:
       - FIFO: key = get_time_ms()  (request arrival time)
       - EDF:  key = coder.last_compile_start + sim.time_to_burnout  (deadline)
    3. heap_push(dongle.wait_queue, coder.id, key)
    4. while (dongle.held
             OR get_time_ms() < dongle.release_time + sim.dongle_cooldown
             OR heap_peek(dongle.wait_queue) != coder.id):
         pthread_cond_wait(dongle.cond, dongle.mutex)
         if sim_over → unlock, return error
    5. heap_pop(dongle.wait_queue)
    6. dongle.held = 1
    7. unlock dongle.mutex
    8. log "X has taken a dongle"
```

### Monitor Thread — Burnout Detection
- Runs in a tight loop with ~1ms `usleep` between checks
- For each coder: if `elapsed_ms() - coder.last_compile_start >= time_to_burnout` → burnout
- Sets `sim_over = 1` (under `sim_mutex`), prints burnout log, broadcasts all dongle condvars to wake sleeping coders
- Also checks completion: if all `coder.compile_count >= num_compiles_req` → graceful stop

### Precise Sleep
`usleep()` alone is imprecise. For compile/debug/refactor durations:
```
ft_sleep(duration_ms, sim):
    target = get_time_ms() + duration_ms
    while get_time_ms() < target:
        if sim_over → return
        remaining = target - get_time_ms()
        if remaining > 1:
            usleep(500)   // sleep most of the way
        else:
            usleep(100)   // fine-grained tail
```

---

## Build Order (Recommended Implementation Sequence)

| Phase | Files | What to Build |
|---|---|---|
| **1. Foundation** | `codexion.h`, `time_utils.c`, `logging.c` | Structs, time helpers, thread-safe logging |
| **2. Heap** | `heap.c` | Min-heap with push/pop/peek — test independently |
| **3. Init + Cleanup** | `init.c`, `cleanup.c` | Allocate everything, destroy everything — test for leaks |
| **4. Dongle Logic** | `dongle.c` | Acquire/release with cooldown + scheduling — the hardest part |
| **5. Coder Thread** | `coder.c` | Full compile→debug→refactor cycle |
| **6. Monitor** | `monitor.c` | Burnout detection + completion check |
| **7. Main** | `main.c` | Argument parsing, orchestration, thread launch/join |
| **8. Testing** | — | Edge cases, valgrind, helgrind/tsan |

---

## Verification Plan

### Automated Tests
```bash
# Basic functionality (should complete without burnout)
./codexion 4 800 200 200 200 3 50 fifo
./codexion 4 800 200 200 200 3 50 edf

# 1 coder edge case
./codexion 1 800 200 200 200 3 50 fifo

# Burnout scenario (time_to_burnout too tight)
./codexion 4 300 200 200 200 3 50 fifo

# Invalid inputs (should error)
./codexion -1 800 200 200 200 3 50 fifo
./codexion 4 800 200 200 200 3 50 invalid
./codexion abc 800 200 200 200 3 50 fifo

# Memory leak check
valgrind --leak-check=full ./codexion 4 800 200 200 200 3 50 fifo

# Thread sanitizer (data races)
# Recompile with -fsanitize=thread, then run
```

### Manual Verification
- Verify log output format matches PDF exactly
- Verify burnout is detected within 10ms
- Verify no log lines are interleaved
- Verify each "is compiling" is preceded by exactly two "has taken a dongle" lines
- Verify simulation stops cleanly (all threads joined, no hangs)

---

## README Requirements (from PDF)

The README.md must include these specific sections:
1. First line: `*This project has been created as part of the 42 curriculum by <login>.*`
2. **Description** — project goal and overview
3. **Instructions** — compilation and execution
4. **Resources** — references + AI usage description
5. **Blocking cases handled** — deadlock prevention (Coffman's conditions), starvation prevention, cooldown handling, burnout detection, log serialization
6. **Thread synchronization mechanisms** — explain pthread_mutex_t, pthread_cond_t usage, race condition prevention, thread-safe communication between coders and monitor

Written in English.
