use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn read_file(path: String) -> Result<Vec<String>, Box<dyn std::error::Error>> {
    let mut inputs: Vec<String> = Vec::new();
    for res in BufReader::new(File::open(path)?).lines() {
        let line = res?;
        inputs.push(line);
    }

    Ok(inputs)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn read_file_success() {
        let mut want: Vec<String> = Vec::new();
        want.push(String::from("a"));
        want.push(String::from("b c"));
        want.push(String::from("d123"));
        let got = read_file(String::from("./tests/read_file_normal.txt"));
        if got.is_err() {
            panic!("Failed to open file");
        }
        assert_eq!(want, got.unwrap());
    }

    #[test]
    fn read_file_fail() {
        let got = read_file(String::from("./tests/not_exists_file_example.txt"));
        assert!(got.is_err());
    }
}
