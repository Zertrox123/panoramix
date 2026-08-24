# Panoramix

Concurrent multithreaded simulation solving the sleeping druid / philosopher problem in C.

## Overview

Demonstrates strict synchronization across multiple POSIX threads using mutexes and semaphores without deadlocks or race conditions.

## Getting Started

### Build & Run

```bash
# Compile
make

# Run simulation: ./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
./panoramix 3 5 2 3
```
