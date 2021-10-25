mod file;

use std::{env, process};

fn main() {
    let _args: Vec<String> = env::args().collect();
    if env::args().count() != 2 {
        eprintln!("The source file is not specified.");
        process::exit(1);
    }
}
