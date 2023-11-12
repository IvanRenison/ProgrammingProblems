// https://codeforces.com/gym/103960/problem/D

fn solve(n: usize, x: usize) -> usize {
    if x == (1 << (n - 1)) { // 2 ^ (n - 1)
        0
    } else if x < (1 << (n - 1)) { // 2 ^ (n - 1)
        1 + solve(n, x * 2)
    } else {
        solve(n, (1 << n) - x)
    }
}

// main function
fn main() {
    // Read 3 naturals from stdin
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    let mut iter = line.split_whitespace();
    let n: usize = iter.next().unwrap().parse().unwrap();
    let x: usize = iter.next().unwrap().parse().unwrap();
    // No need to parse y

    let res: usize = solve(n, x);
    println!("{res}");
}
