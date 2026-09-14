*This project has been created as part of the 42 curriculum by ynascime.*

# Codexion

## Description

Codexion simulates a group of coders working around a shared circular co-working hub with a limited pool of USB dongles. Compiling requires two dongles at once — one shared with each neighbor — so coders inevitably compete for the same physical resources. Each coder cycles endlessly through three phases: **compiling** (holding two dongles), **debugging**, and **refactoring**, and must get back to compiling before a configurable **burnout** deadline expires, or the simulation ends in failure.

The real subject of the project is concurrent resource arbitration: one POSIX thread per coder, plus a dedicated monitor thread, all sharing a small pool of mutex-protected resources. The program has to guarantee mutual exclusion, fairness, and liveness under two different scheduling policies (`fifo` and `edf`) without ever deadlocking, starving a coder, or missing a burnout deadline by more than 10ms.

## Instructions

### Build

```
make
```

This produces the `codexion` binary at the project root. `make clean` removes object files, `make fclean` also removes the binary, and `make re` rebuilds everything from scratch.

### Run

```
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

| Argument | Meaning |
|---|---|
| `number_of_coders` | Number of coder threads, and dongles. Must be a positive integer below 500. |
| `time_to_burnout` | Milliseconds a coder can go without starting a compile before burning out. |
| `time_to_compile` | Milliseconds a coder spends compiling (holding two dongles). |
| `time_to_debug` | Milliseconds a coder spends debugging. |
| `time_to_refactor` | Milliseconds a coder spends refactoring. |
| `number_of_compiles_required` | Simulation stops successfully once every coder reaches this many compiles. |
| `dongle_cooldown` | Milliseconds a dongle stays unavailable after being released. |
| `scheduler` | Arbitration policy for dongle requests: `fifo` or `edf`. |

Example:

```
./codexion 5 800 200 100 100 5 100 edf
```

Every state change is logged as `<timestamp_ms> <coder_id> <event>`, e.g. `402 3 is compiling`. The simulation ends either the moment every coder reaches `number_of_compiles_required`, or the moment any coder burns out — whichever comes first.

## Resources

- [POSIX Threads Programming (LLNL tutorial)](https://hpc-tutorials.llnl.gov/posix/)
- `man pthread_mutex_lock`, `man pthread_cond_wait`, `man pthread_create`
- Dijkstra's Dining Philosophers problem — the classic analogue for this resource-sharing scenario
- Coffman's four conditions for deadlock (mutual exclusion, hold-and-wait, no preemption, circular wait)
- Liu & Layland, *Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment* (1973) — origin of Earliest Deadline First scheduling
- Binary heap / priority queue data structure (standard reference: Cormen et al., *Introduction to Algorithms*)

## Blocking cases handled

- **Deadlock prevention (Coffman's conditions):** each coder's two dongles are assigned once at startup so that `dongle_a` always refers to the lower-indexed dongle and `dongle_b` to the higher-indexed one, regardless of which physical dongle is on the coder's left or right. Every coder therefore always attempts acquisition in the same global order, which removes the circular-wait condition that dining-philosophers-style deadlocks depend on. `take_dongle()` also never holds one dongle while blocking indefinitely for the second — if the second isn't available, the first is released immediately, avoiding an unbounded hold-and-wait.
- **Starvation prevention:** under `fifo`, coders are served strictly in arrival order through a shared linked-list queue; a coder can only attempt acquisition once it reaches the front, and the front advances every time a coder is served. Under `edf`, a binary min-heap orders waiting coders by burnout deadline (`last_compile_start + time_to_burnout`); a coder only proceeds once it holds the earliest deadline among itself and its two dongle-sharing neighbors, so the most urgent coder is always served first without permanently starving anyone else.
- **Cooldown handling:** each dongle stores its own cooldown timestamp, set to `now + dongle_cooldown` on release. Acquisition checks this timestamp before granting the dongle, so it stays unavailable for the full window under either scheduler.
- **Precise burnout detection:** a dedicated monitor thread polls every coder's last-compile-start timestamp at a very fine interval (every 0.1ms), so burnout is always detected and logged well within the required 10ms window.
- **Log serialization:** every log line is written through a single shared print mutex, so two threads can never interleave partial output even when they log at effectively the same millisecond.

## Thread synchronization mechanisms

- **One `pthread_mutex_t` per dongle** doubles as both the "is this dongle currently held" state and the guard on its cooldown timestamp. Acquiring a dongle *is* locking its mutex; releasing it *is* unlocking it — the OS-level mutex itself enforces mutual exclusion, rather than a separate flag that could be checked and set non-atomically.
- **`sim_mutex`** guards the single "simulation active" flag that every coder thread and the monitor read on every loop iteration, and that the monitor writes exactly once when the simulation ends.
- **`print_mutex`** serializes every `printf` call across every coder thread and the monitor.
- **Per-coder `finish_mutex` / `burnout_mutex`:** each coder's "finished" flag and last-compile-start timestamp are written by that coder's own thread but read concurrently by the monitor thread; both sides go through the same mutex so the monitor never observes a half-written value.
- **FIFO queue (list mutex + condition variable):** a shared linked list protected by one mutex; a coder that isn't at the front blocks on the condition variable instead of busy-waiting, and is woken by a broadcast whenever a dongle is released or the queue advances.
- **EDF heap (heap mutex + condition variable):** a shared array-based binary min-heap, same pattern — protected by a mutex, waiters block on a condition variable, and are woken by a broadcast on every release or heap change.

Concrete example of a race this prevents: without the dongle's own mutex acting as the take/release mechanism, two coders could both observe "dongle available" before either one flags it as taken. Here, locking the dongle's mutex *is* the atomic "take" operation, so a second coder attempting the same dongle simply blocks until the first releases it — there is no window where both could believe they succeeded.

**AI usage:** An AI assistant (Claude) was used throughout development for: reviewing the codebase section-by-section against the project subject and flagging missing or non-compliant requirements; diagnosing two concurrency bugs behind a reproducible segfault (an indexing bug in per-coder dongle initialization. This README was also drafted with AI assistance and reviewed by the author.
