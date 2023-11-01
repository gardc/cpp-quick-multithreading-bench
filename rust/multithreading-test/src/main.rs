extern crate rayon;

use rayon::prelude::*;
use std::time::Instant;
use std::sync::{Arc, Mutex};

fn fibonacci(n: u32) -> u64 {
    match n {
        0 => 0,
        1 => 1,
        _ => fibonacci(n - 1) + fibonacci(n - 2),
    }
}

fn main() {
    const X: u32 = 43;
    let v1: Arc<Mutex<Vec<u64>>> = Arc::new(Mutex::new(Vec::new()));

    // Multi-threaded using rayon
    let start_time = Instant::now();
    (0..100).into_par_iter().for_each(|_| {
        let result = fibonacci(X);
        let mut v = v1.lock().unwrap();
        v.push(result);
    });

    let elapsed_time = start_time.elapsed();
    println!("Time taken in multithreaded system to calculate fib({}): {:?}", X, elapsed_time);
    println!("Concurrent vector (first 3): {:?}", &v1.lock().unwrap()[..3]);

    // Single-threaded
    let start_time2 = Instant::now();
    let mut v2: Vec<u64> = Vec::new();
    for i in 0..100 {
        println!("Calculating fib({i})");
        let result = fibonacci(X);
        v2.push(result);
    }
    
    let elapsed_time2 = start_time2.elapsed();
    println!("Time taken in single threaded system to calculate fib({}): {:?}", X, elapsed_time2);
    println!("Single-threaded vector (first 3): {:?}", &v2[..3]);
}
