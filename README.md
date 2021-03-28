# Chicken Simulator

Attempts to solve a problem I saw in a YouTube video by brute force.

> In a barn, 100 chicks sit peacefully in a circle. Suddenly, each chick
randomly pecks the chick immediately to its left or right. What is the
expected number of unpecked chicks?

### Python Implementation
Quick, lazy, and doomed to be slow from the start.  
Requires Python3, no additional dependencies, works well enough.

### C Implementation
This isn't even optimised and it runs literally 200x faster on my PC (i5-7200u).
Compile with either GCC or Clang, `$C -O3 main.c` for best results.