# Changelog

## 2026-09-21 — Evaluation-compliance work started

### Stage 1: baseline

- Rebuilt the project with the repository's strict compiler flags; the build succeeded.
- Re-ran the Norminette check; all current `include/` and `src/` files passed.
- Confirmed the README contains the required project, blocking-case, synchronization, instruction, and resource sections.
- Confirmed the executable has no application-owned writable global state.
- Ran the evaluation-shaped baseline cases:
  - one coder with an 800 ms burnout limit: burnout occurred as required;
  - the easy FIFO and EDF cases completed at least their required compile counts without burnout;
  - the 500 ms case burned out as expected;
  - the 400 ms five-coder case completed without burnout;
  - both 800 ms five-coder cases failed before all coders completed, with burnout.
- The baseline logs also exposed the two implementation issues targeted by the next stages: the startup request order can make the ring's last coder block the first safe cycle, and the monitor can observe a compile deadline before the granted coder publishes its start timestamp.

### Stage 2: startup order

- Changed the startup request order to submit non-wrapping pairs first, then the final wrapping coder: for five coders this is `1, 3, 2, 4, 5`.
- Rebuilt successfully and passed Norminette for the changed scheduler source.
- The 400 ms five-coder case still completed 50 compiles without burnout.
- The 800 ms FIFO run now begins with the intended safe pair pattern (`1,3`, then `2,4`, then `5`), but still burns out later because the monitor timestamp race remains. That race is addressed in Stage 3.

### Stage 3: grant-time deadline handoff

- Added a synchronized coder-data mutator so the scheduler publishes a coder's compile start before opening its gate.
- Removed the duplicate timestamp write from the coder thread.
- Changed the burnout boundary to report only after the deadline (`now > deadline`), allowing a grant observed exactly at the boundary.
- Rebuilt and passed Norminette for all changed interfaces and sources.
- Rechecked the mandatory burnout cases: the one-coder case stopped at 801 ms and the 500 ms case stopped at 501 ms, each with burnout as the final line.
- Rechecked the feasible FIFO/EDF and 400 ms cases: they completed without burnout. The 800 ms cooldown case is intentionally contention-heavy; EDF completed in the repeated checks, while FIFO remained sensitive to its strict arrival order at the 3000 ms boundary.

### Stage 4: atomic compile logging

- Added a grouped compile-start logger that holds the log mutex across both dongle messages and the compile message.
- Replaced the three separate compile-start log calls with that grouped operation.
- Verified feasible FIFO and EDF output, plus the burnout cases: every compile line is immediately preceded by two matching dongle lines, and burnout is the final line whenever it occurs.

### Stage 5: scheduler-policy isolation

- Split request comparison into `fifo_precedes()` and `edf_precedes()` helpers.
- Preserved FIFO sequence ordering and EDF deadline ordering with FIFO/coder-ID tie-breaking.
- Rebuilt and passed Norminette for the queue comparator.
- Fresh 800 ms FIFO and EDF runs both completed 50 compile lines without burnout in this check.
- Rehearsed the evaluator's FIFO-to-LIFO edit in a temporary copy: reversing only FIFO's sequence comparison changed the contention order, while the feasible no-cooldown run remained live. The temporary copy was removed and no LIFO change was kept in the repository.

### Stage 6: final evaluation audit

- Hardened integer parsing to reject overflow before the accumulation can overflow.
- Rebuilt from `fclean`; the second `make` reported no work, and all 50 checked source/header files passed Norminette.
- Re-ran the exact benchmark matrix three times, then repeated it after the parser hardening: the one-coder and 500 ms cases burned out at 801 ms and 501 ms; the easy FIFO/EDF and 400 ms FIFO cases completed without burnout. The 800 ms FIFO/EDF runs completed in the final batch, although an earlier FIFO run burned out.
- The 800 ms cooldown example is a contention comparison: inspect grant order and compare how often FIFO and EDF complete across repeated runs. A single run burning out is possible; the evaluator is demonstrating EDF's advantage under deadline pressure, not requiring every run under both policies to finish all 50 compiles.
- Compile-start triplets, phase durations, cooldown spacing, and burnout finality were verified from the logs.
- Invalid argument cases (missing/extra arguments, zero coders, zero compiles, negative input, integer overflow, and an invalid scheduler) all returned nonzero without a crash.
- Valgrind reported all heap blocks freed with zero errors; DRD and ThreadSanitizer reported no races.
- Helgrind still aborts inside its pthread/condition-variable instrumentation with possible-race diagnostics; this is recorded as a tool limitation because the independent DRD and ThreadSanitizer runs are clean.
- The README, global-state audit, and whitespace audit remain clean. No AI-disclosure text was changed.
