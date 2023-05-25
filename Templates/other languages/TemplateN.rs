//

use std::io;
use std::str::FromStr;

fn read_line() -> String {
    let mut buffer = String::new();
    io::stdin()
        .read_line(&mut buffer)
        .expect("failed to read line");

    buffer.trim().to_string()
}

fn read<T : FromStr>() -> Result<T, T::Err>{
    read_line().trim().parse::<T>()
}

fn read_vec<T : FromStr>() -> Result< Vec<T>, T::Err>{
    read_line().split_whitespace().map(|x| x.parse::<T>()).collect()
}

fn parse1() {

}

fn solve1() {

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