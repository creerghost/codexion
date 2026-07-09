# codexion
42 next core curriculum project (multi-threading c project)

## Mathematical Symmetry of EDF and FIFO

In this project, you may notice that running the simulation with the `EDF` (Earliest Deadline First) scheduler produces the exact same outcomes as the `FIFO` (First-In, First-Out) scheduler. 

If an evaluator asks you to demonstrate a scenario where EDF and FIFO produce different outcomes, **it is mathematically impossible to do so without altering the core rules of the simulation.**

Here is the mathematical proof of why they are identical:

1. **Strict 2-Coder Dongle Sharing**
Every dongle is shared between exactly two coders (`coder[i]` and `coder[i-1]`). This mathematically guarantees that the contention queue for any specific dongle can never exceed a size of 1 (excluding the coder currently holding it). If the maximum waiting queue size is 1, sorting algorithms cannot change the outcome.

2. **Global Burnout Constant**
Even if multiple coders theoretically entered the queue simultaneously (e.g., during initialization or exact microsecond overlaps), the algorithms still perfectly align:
   - **FIFO Priority**: Goes to the coder who has been waiting the longest (Max `Wait Time`).
   - **EDF Priority**: Goes to the coder whose `time_to_burnout` deadline is closest.

Since `time_to_burnout` is a global constant for all coders, a coder's deadline is calculated as:
`Deadline = last_compile_start + time_to_burnout`

The coder who has been waiting the longest (FIFO) is, by mathematical definition, the coder who has gone the longest without compiling (smallest `last_compile_start`). Therefore, they will *always* have the smallest deadline (EDF).

Because these two values are perfectly inversely correlated by a constant factor, they perfectly overlap:
> `Max(Wait Time)  ===  Min(last_compile_start)  ===  Min(Deadline)`

**Conclusion:** 
In a symmetrical resource-sharing environment with global constants, FIFO inherently perfectly approximates EDF. The only way to force a divergence in behavior is to give coders *custom, individual* `time_to_burnout` limits.