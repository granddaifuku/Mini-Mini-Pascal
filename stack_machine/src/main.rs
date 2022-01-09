mod file;
mod operate;

use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        panic!("Number of args should be 2");
    }
    let inputs = file::read_file(args[1].clone()).unwrap();
    let mut buf: Vec<u8> = Vec::new();
    operate::process(&mut buf, &inputs)
}
