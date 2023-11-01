# Quick test of multithreading in C++ using Intel's TBB library
The test is for how much time is spent doing 100 x fibbonacci(40) in a single thread vs multithreaded.
- Result for multithreading debug build (16 logical processors): ~9 seconds
- Result for single thread debug build: ~73 seconds

## Single threaded (debug build)
Calculating fibbonacci(40) 100 times in a single thread gave these results on my system:
```
Time taken in single threaded system to calculate fib(40): 72.9999s
single threaded vector (first 3):
102334155 | 102334155 | 102334155 |
```
![single threaded task manager screenshot](./single.png)

## Multi threaded (debug build)
Calculating fibbonacci(40) 100 times multithreaded gave these results on my 16 logical processors system:
```
Time taken in multithreaded system to calculate fib(40): 9.10323s
concurrent vector (first 3):
102334155 | 102334155 | 102334155 |
```
![multithreaded task manager screenshot](./multi.png)

## Release build results:
- fibonnacci(40) 100 times:
	```
	Time taken in multithreaded system to calculate fib(40): 3.17961s
	concurrent vector (first 3):
	102334155 | 102334155 | 102334155 |

	Time taken in single threaded system to calculate fib(40): 0.31893s
	single threaded vector (first 3):
	102334155 | 102334155 | 102334155 |
	```
- fibonnaci(43) 100 times:
	```
	Time taken in multithreaded system to calculate fib(43): 12.8587s
	concurrent vector (first 3):
	433494437 | 433494437 | 433494437 |

	Time taken in single threaded system to calculate fib(43): 1.35241s
	single threaded vector (first 3):
	433494437 | 433494437 | 433494437 |
	```
Seems that the Release build optimizes the single threaded version by detecting that it's calling the same fib function 100 times in a row and uses a single result.

# Rust
I also made a Rust version of this test, which seems to be faster! Unexpected, but I'm sure the C++ could be optimized better.
```
Time taken in multithreaded system to calculate fib(43): 9.38572s
Concurrent vector (first 3): [433494437, 433494437, 433494437]

Time taken in single threaded system to calculate fib(43): 77.5547496s
Single-threaded vector (first 3): [433494437, 433494437, 433494437]
```
*The Release version here also optimized the single threaded 100-iter away to just 1, but I added a `println!` which made it iterate over every iteration*