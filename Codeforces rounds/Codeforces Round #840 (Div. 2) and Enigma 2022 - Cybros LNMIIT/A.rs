// https://codeforces.com/contest/1763/problem/A

use std::io;
use std::str::FromStr;

fn solve1(As: Vec<u16>) -> u16 {

    let mut bits0: [bool; 10] = [false; 10];
    let mut bits1: [bool; 10] = [false; 10];

    for a in As {
        for i in 0..10 {
            if a & (1 << i) != 0 {
                bits1[i] = true;
            } else {
                bits0[i] = true;
            }
        }
    }

    let mut max: u16 = 0;
    let mut min: u16 = 0;
    for i in 0..10 {
        if bits1[i] {
            max += 1 << i;
        }
        if !bits0[i] {
            min += 1 << i;
        }
    }

    max - min
}

fn read_line() -> String {
    let mut buffer = String::new();
    io::stdin()
        .read_line(&mut buffer)
        .expect("failed to read line");

    buffer.trim().to_string()
}

fn read<T : FromStr>() -> Result<T, T::Err>{
    read_line().parse::<T>()
}

fn read_vec<T : FromStr>() -> Result< Vec<T>, T::Err>{
    read_line().split_whitespace().map(|x| x.parse::<T>()).collect()
}

fn parse1() -> Vec<u16> {

    // Parse n
    let _n: usize = read().unwrap();

    // Parse As
    read_vec().unwrap()
}

fn main() {
    // Parse t
    let t: usize = read().unwrap();

    for _ in 0..t {
        let data = parse1();
        let res = solve1(data);
        println!("{res}");
    }
}
