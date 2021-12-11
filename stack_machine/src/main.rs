mod file;

use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        panic!("Number of args should be 2");
    }
    let _ = file::read_file(args[1].clone());
}
