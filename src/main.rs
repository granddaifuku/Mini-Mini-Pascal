mod file;

use std::{env, process};

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        eprintln!("The source file is not specified.");
        process::exit(1);
    }
}
