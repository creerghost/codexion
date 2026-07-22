*This project has been created as part of the 42 curriculum by vlnikola.*


# Codexion

## Table of Contents

1. [Description](#description)
2. [Instructions](#instructions)
   - [Prerequisites](#prerequisites)
   - [Compilation](#compilation)
   - [Execution](#execution)
   - [Usage Examples](#usage-examples)
   - [Tests](#tests)
3. [Understanding Concurrency](#understanding-concurrency--the-bank-analogy)
4. [Simulation Pipeline Breakdown](#simulation-pipeline-breakdown)
5. [Thread Synchronization Mechanisms](#thread-synchronization-mechanisms)
6. [Blocking Cases Handled](#blocking-cases-handled)
7. [Resources](#resources)

---

## Description

Codexion is a highly-concurrent multithreaded simulation written in C that models resource sharing among competing processes. It serves as a practical exploration of classic concurrency challenges, specifically **deadlock avoidance**, **starvation prevention**, and **fair resource scheduling** in a strict-timing environment.

The simulation models a scenario where multiple threads — referred to as **coders** — alternate between three execution phases: *compiling*, *debugging*, and *refactoring*. Entering the compiling phase requires simultaneously acquiring two shared resources called **dongles**. There are exactly as many dongles as there are coders, arranged in a circular topology where each dongle sits between two adjacent coders. This is a direct, faithful adaptation of the classic **Dining Philosophers problem**.

If a coder fails to acquire resources and begin compiling within a `time_to_burnout` deadline, it **burns out** and the simulation terminates immediately. To guarantee liveness, the simulation implements fair arbitration using custom **binary-heap priority queues**, supporting both **FIFO** (First In, First Out) and **EDF** (Earliest Deadline First) scheduling policies.

---

## Instructions

### Prerequisites

- A Unix-like operating system (Linux, macOS, or WSL) with POSIX threads support
- A standard C compiler: `cc`, `gcc`, or `clang`
- `make` utility

### Compilation

The project ships with a comprehensive Makefile, compiled under strict flags (`-Wall -Wextra -Werror -pthread`).

```bash
make        # Compile the 'codexion' binary
make re     # Clean recompile from scratch
make clean  # Remove object files
make fclean # Remove object files and the final executable
```

### Execution

```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> \
           <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

**Argument Reference:**

| Argument | Type | Description |
|---|---|---|
| `number_of_coders` | `int` | Number of concurrent coders (equals total number of dongles). |
| `time_to_burnout` | `ms` | Max milliseconds allowed between compile starts before a coder burns out. |
| `time_to_compile` | `ms` | Duration of the compile phase — coder holds 2 dongles throughout. |
| `time_to_debug` | `ms` | Duration of the debugging phase. |
| `time_to_refactor` | `ms` | Duration of the refactoring phase. |
| `number_of_compiles_required` | `int` | Simulation ends cleanly when every coder reaches this count. Use `0` for infinite. |
| `dongle_cooldown` | `ms` | Milliseconds a dongle remains unavailable after being released. |
| `scheduler` | `string` | Arbitration policy: `fifo` (arrival order) or `edf` (closest deadline first). |

### Usage Examples

```bash
# 5 coders, 800ms burnout limit, 200ms per phase, 7 compiles each, 50ms cooldown — FIFO scheduling
./codexion 5 800 200 200 200 7 50 fifo

# Same scenario with Earliest Deadline First scheduling
./codexion 5 800 200 200 200 7 50 edf

# Stress test: 4 coders, tight 410ms burnout window, zero cooldown
./codexion 4 410 200 200 0 5 0 fifo
```

**Expected log output format:**

```
0    1 has taken a dongle
1    1 has taken a dongle
1    1 is compiling
201  1 is debugging
401  1 is refactoring
402  2 has taken a dongle
403  2 has taken a dongle
403  2 is compiling
603  2 is debugging
803  2 is refactoring
1204 3 burned out
```

### Tests

A dedicated test suite is located in `tests/`:

```bash
make test          # Run simulation integration tests
make test-all      # Run all available tests
make test-parser   # Run parser-specific tests
make test-heap     # Run priority queue (heap) unit tests
make test-dongle   # Run dongle synchronization tests
```

---

## Understanding Concurrency

To understand the core challenges of Codexion and the Dining Philosophers problem, it helps to step away from code and look at a real-world analogy: **bank accounts**.

### 1. Multithreading & The Data Race

Imagine a bank account with a starting balance of `$100`. Two separate tellers (Thread A and Thread B) receive a `$50` deposit at the exact same millisecond.

Processing a deposit involves three steps:

1. **Read** the current balance
2. **Add** the deposit amount
3. **Write** the new balance back

Without synchronization, the threads interleave:

```
Thread A (Read)  → sees $100
Thread B (Read)  → sees $100
Thread A (Write) → calculates $100 + $50, writes $150
Thread B (Write) → calculates $100 + $50, writes $150  ← Thread A's write is lost
```

The final balance is `$150` instead of `$200`. This is a **data race** — two threads racing to modify shared memory, causing corruption.

**The fix: Mutexes.** Thread A locks the account, reads `$100`, writes `$150`, and unlocks. Thread B waits until the lock is released. No more corruption.

---

### 2. The Deadlock Problem

Locks prevent data races, but introduce a new hazard: **deadlocks**.

Consider two simultaneous transfers:

- **Thread 1:** Transfer `$100` from Account A → Account B
- **Thread 2:** Transfer `$50` from Account B → Account A

Each thread must lock *both* accounts to safely move money. Here's what goes wrong:

```
Thread 1 locks Account A.
Thread 2 locks Account B.
Thread 1 waits for Account B  → blocked by Thread 2.
Thread 2 waits for Account A  → blocked by Thread 1.
```

Both threads sleep, holding one lock each, waiting for the other forever. **The system freezes.** This is a deadlock.

---

### 3. Connection to Dining Philosophers & Codexion

The bank transfer deadlock is precisely the **Dining Philosophers problem**:

| Analogy | Codexion Equivalent |
|---|---|
| Bank accounts | Dongles |
| Tellers | Coders |
| Transfer requiring both accounts | Compiling requiring both dongles |

Five coders sit in a circle. Each needs their left and right dongle to compile. If all five simultaneously grab their left dongle, every dongle is taken — and every coder waits forever for their right one. **Deadlock.**

**How Codexion solves it: Global Lock Ordering.**

In the bank example, you break deadlock by enforcing a rule: *"Always lock the account with the smaller ID first."*

- Thread 1 (A→B): Locks A (smaller), then B. ✓
- Thread 2 (B→A): Must lock A first, but Thread 1 holds it — so Thread 2 waits in line. No circular wait.

Codexion applies the same principle. A coder never blindly grabs "left then right." Instead:

```c
first_dongle  = min(left_id, right_id);  // Always lock this first
second_dongle = max(left_id, right_id);  // Then lock this
```

This mathematically eliminates the possibility of a circular wait, satisfying the Coffman condition analysis and guaranteeing deadlock freedom.

---

## Simulation Pipeline Breakdown

### 1. Initialization (`inits/`)

The program parses command-line arguments into a central `t_context` structure and allocates arrays of `t_coder` and `t_dongle` structs. During `init_coders`, each coder identifies its adjacent left and right dongles and assigns them to `first_dongle` (minimum index) and `second_dongle` (maximum index), enforcing the global lock-ordering strategy upfront.

### 2. Thread Spawning (`start_sim`)

A `start_time` timestamp is recorded — this is the epoch from which all burnout timers begin counting. The main process calls `pthread_create` to spawn one thread per coder, plus one dedicated `monitor` thread.

### 3. The Coder Lifecycle

Each coder thread runs an infinite loop (`while(is_sim_running)`) through four distinct phases:

**Phase A — Acquiring Dongles**
The coder requests `first_dongle` then `second_dongle`. For each dongle, it locks the dongle's mutex, inserts its ID into the dongle's binary-heap priority queue (timestamp for FIFO, or burnout deadline for EDF), and enters `pthread_cond_wait`. It wakes up and claims the dongle only when it reaches the top of the heap *and* the dongle's cooldown has fully expired.

**Phase B — Compiling**
With both dongles acquired, the coder locks its personal mutex, increments `compile_count`, updates `last_compile_start` (resetting the burnout countdown), logs `"is compiling"`, and sleeps for `time_to_compile` milliseconds.

**Phase C — Releasing Dongles**
The coder drops both dongles, sets their state to available, records the `release_time` to begin the cooldown window, and calls `pthread_cond_broadcast` to wake any waiting neighbours.

**Phase D — Debugging & Refactoring**
The coder logs and sleeps through each remaining phase, then loops back to Phase A.

### 4. The Monitor

Running in parallel with the coders, the monitor executes a tight ~1ms polling loop with two responsibilities:

- **Burnout detection:** Locks each coder's mutex, reads `last_compile_start`, and compares elapsed time against `time_to_burnout`. On burnout, it flips the global `is_running` flag, logs the death, and broadcasts a shutdown signal — all within the required 10ms threshold.
- **Completion check:** If all coders have reached `number_of_compiles_required`, it initiates a clean shutdown.

### 5. Teardown

Once `is_running` is false, coder threads exit their loops. The main thread calls `pthread_join` to collect all children, then destroys all mutexes and condition variables, frees all allocated memory, and exits cleanly.

---

## Thread Synchronization Mechanisms

### Primitives Used

Codexion relies on the following `pthread` API functions:

| Function | Role |
|---|---|
| `pthread_create` | Spawns coder and monitor threads. |
| `pthread_join` | Blocks the main thread until all children exit cleanly. |
| `pthread_mutex_init` / `_destroy` | Allocates and frees mutex locks at startup and teardown. |
| `pthread_mutex_lock` / `_unlock` | Marks the boundaries of critical sections throughout execution. |
| `pthread_cond_init` / `_destroy` | Sets up and tears down condition variables (dongle wait queues). |
| `pthread_cond_wait` | Puts a coder to sleep, atomically releasing the dongle's mutex. |
| `pthread_cond_broadcast` | Wakes all threads sleeping on a dongle's condition variable upon release. |

---

### Condition Variables: With vs. Without

Condition variables are not a mere optimization — they are architecturally essential.

**Without condition variables (busy-waiting):**

```c
// BAD: Burns CPU, introduces artificial latency, scales poorly
while (1) {
    pthread_mutex_lock(&dongle->mutex);
    if (dongle->held == false && ft_heappeek(&dongle->heapq) == coder->id)
        break;
    pthread_mutex_unlock(&dongle->mutex);
    usleep(100);  // Sleep and retry — repeatedly
}
```

**With condition variables (Codexion's approach):**

```c
// CORRECT: 0% CPU while waiting, instant wakeup on signal
pthread_mutex_lock(&dongle->mutex);
while (dongle->held == true || ft_heappeek(&dongle->heapq) != coder->id)
    pthread_cond_wait(&dongle->cond, &dongle->mutex);  // Atomically sleeps + unlocks

ft_heappop(&dongle->heapq, &tmp);
dongle->held = true;
pthread_mutex_unlock(&dongle->mutex);
```

`pthread_cond_wait` guarantees zero CPU consumption while blocking, microsecond-precision wakeup the moment a dongle is released, and automatic mutex reacquisition upon waking — with no risk of a race between the check and the sleep.

---

### Mutex Hierarchy

To prevent nested-lock deadlocks, a strict acquisition order is enforced across all four mutex types:

| # | Mutex | Protects |
|---|---|---|
| 1 | `dongle->mutex` | `held`, `release_time`, and the heap priority queue. Acquired in ascending index order. |
| 2 | `coder->mutex` | `last_compile_start` and `compile_count`. Prevents the monitor from reading a half-updated timestamp mid-reset. |
| 3 | `ctx->log_mutex` | Serializes `printf` output. Prevents character interleaving in terminal logs. |
| 4 | `ctx->sim_mutex` | Protects the global `is_running` boolean. Eliminates TOCTOU windows during shutdown. |

---

## Blocking Cases Handled

**1. Deadlock Prevention (Coffman's Conditions)**
By forcing all coders to always acquire the dongle with the lowest numerical index first, the implementation intentionally breaks Coffman's *Circular Wait* condition. A cyclic dependency in the wait graph is mathematically impossible.

**2. Starvation Prevention (Fair Scheduling)**
A min-heap priority queue prevents thundering-herd starvation. Under `fifo`, early arrivers are guaranteed access in order. Under `edf`, coders nearest their burnout deadline jump the queue, guaranteeing liveness under tight constraints.

**3. Dongle Cooldown Enforcement**
A `release_time` timestamp is recorded when a dongle is dropped. Threads that wake up and find the cooldown still active return to sleep immediately, and are re-signaled once the cooldown expires.

**4. Precise Burnout Detection**
A dedicated monitor thread runs a tight 1ms polling loop, independent of all coder threads. Even if every coder is blocked or sleeping, the monitor accurately detects burnout and logs it within the required 10ms threshold.

**5. Log Serialization**
All terminal output routes through a single `log_msg()` wrapper that acquires `log_mutex` before writing. This makes every log line atomic with respect to all other threads.

**6. Single-Coder Edge Case**
When `number_of_coders == 1`, there is only one dongle on the table — but compiling requires two. The codebase detects this edge case, allows the coder to pick up the single available dongle, and waits for the monitor to declare the inevitable burnout cleanly.

---

## Resources

### References

- [The Dining Philosophers Problem by DeRuina - GitHub](https://github.com/DeRuina/philosophers)
- [The Dining Philosophers by Oceano - Youtube](https://www.youtube.com/watch?v=zOpzGHwJ3MU&t=14s)
- [POSIX Threads Programming — GeeksforGeeks](https://www.geeksforgeeks.org/c/thread-functions-in-c-c/)
- [Coffman Conditions for Deadlock — Wikipedia](https://en.wikipedia.org/wiki/Deadlock#Necessary_conditions)
- [Earliest Deadline First Scheduling — Wikipedia](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling)
- [Binary Heap — Wikipedia](https://en.wikipedia.org/wiki/Binary_heap)
- [Binary Heap - KSVI MFF Charles University](https://ksvi.mff.cuni.cz/~dingle/2019/algs/lecture_10.html)
- [Python subprocess Module - GeeksforGeeks](https://www.geeksforgeeks.org/python/python-subprocess-module/)
- [Makefile Guide by n1kito - GitHub](https://github.com/n1kito/Makefile)

---

### AI Usage Disclosure

AI tools were utilized in this project strictly for the following purposes:
- **Documentation**: Generating and structuring this README, as well as writing the internal C docstrings.
- **Testing Infrastructure**: Guidance on linking Python code with C main executables, and strategies for integrating the Python testing Makefile with the main C Makefile.

No core project code (C source files, algorithms, or synchronization logic) was generated by AI.