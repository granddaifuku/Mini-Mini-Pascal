use std::fs;

#[allow(unused)]
pub fn read(path: String) -> Result<String, Box<dyn std::error::Error>> {
    let content = fs::read_to_string(path)?;

    Ok(content)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn read_success() {
        let actual = read(String::from("./tests/files/read_success.txt")).unwrap();
        let expected = String::from("1 abc あ\ntest\n");
        assert_eq!(actual, expected);
    }

    #[test]
    fn read_no_file() {
        let actual = read(String::from("./tests/files/no_file_example.txt")).unwrap_err();
        assert!(actual.is::<std::io::Error>());
    }
}
