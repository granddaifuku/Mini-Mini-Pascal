mod error;
mod file;
mod tokenize;

use std::{env, process};
use tokenize::Tokenizer;

fn main() {
    let args: Vec<String> = env::args().collect();
    if env::args().count() != 2 {
        eprintln!("The source file is not specified.");
        process::exit(1);
    }
    let user_input = file::read(&args[1]);
    if user_input.is_err() {
        eprintln!("Failed to read file: {}", user_input.unwrap_err());
        process::exit(1);
    }
    let tokenizer = Tokenizer::new();
    let _ = tokenizer.tokenize(user_input.unwrap());
}
