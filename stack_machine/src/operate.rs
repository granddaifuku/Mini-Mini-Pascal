use std::io::{stdout, Write};

const LENGTH: usize = 10000;

#[allow(unused_mut)]
pub fn process<W: Write>(writer: &mut W, operations: &Vec<String>) {
    let mut st: [i32; LENGTH] = [0; LENGTH];
    let mut memory: [i32; 26] = [0; 26];
    let lim = operations.len();
    let mut stack_pointer = 0;
    let mut prog_counter = 0;

    while prog_counter < lim {
        // Split with the blank
        let operation: Vec<&str> = operations[prog_counter].split_whitespace().collect();

        match operation.len() {
            1 => match operation[0] {
                "ADD" => {
                    let a = st[stack_pointer - 1];
                    let b = st[stack_pointer - 2];
                    st[stack_pointer - 2] = a + b;
                    stack_pointer -= 1;
                }
                "SUB" => {
                    let a = st[stack_pointer - 1];
                    let b = st[stack_pointer - 2];
                    st[stack_pointer - 2] = b - a;
                    stack_pointer -= 1;
                }
                "MLT" => {
                    let a = st[stack_pointer - 1];
                    let b = st[stack_pointer - 2];
                    st[stack_pointer - 2] = a * b;
                    stack_pointer -= 1;
                }
                "DIV" => {
                    let a = st[stack_pointer - 1];
                    let b = st[stack_pointer - 2];
                    st[stack_pointer - 2] = b / a;
                    stack_pointer -= 1;
                }
                "EQL" => {
                    let a = st[stack_pointer - 1];
                    let b = st[stack_pointer - 2];
                    stack_pointer -= 2;
                    if a == b {
                        st[stack_pointer] = 1;
                    } else {
                        st[stack_pointer] = 0;
                    }
                }
                "GRT" => {
                    let a = st[stack_pointer - 1];
                    let b = st[stack_pointer - 2];
                    stack_pointer -= 2;
                    if a < b {
                        st[stack_pointer] = 1;
                    } else {
                        st[stack_pointer] = 0;
                    }
                }
                "LET" => {
                    let a = st[stack_pointer - 1];
                    let b = st[stack_pointer - 2];
                    stack_pointer -= 2;
                    if a > b {
                        st[stack_pointer] = 1;
                    } else {
                        st[stack_pointer] = 0;
                    }
                }
                _ => {
                    panic!("Invalid Instruction Code")
                }
            },
            2 => {
                match operation[0] {
                    "GET" => {
                        let var = operation[1];
                        let pos: usize = var.parse().unwrap();
                        // read std in
                        let mut s = String::new();
                        std::io::stdin().read_line(&mut s).ok();
                        memory[pos] = s.trim().parse().ok().unwrap();
                    }
                    "PUT" => {
                        let var = operation[1];
                        let pos: usize = var.parse().unwrap();
                        writeln!(writer, "{}", memory[pos]).unwrap();
                        writeln!(stdout(), "{}", memory[pos]).unwrap();
                    }
                    "LOD" => {
                        let var = operation[1];
                        let pos: usize = var.parse().unwrap();
                        st[stack_pointer] = memory[pos];
                        stack_pointer += 1;
                    }
                    "LDC" => {
                        let var = operation[1];
                        let num: i32 = var.parse().unwrap();
                        st[stack_pointer] = num;
                        stack_pointer += 1;
                    }
                    "STR" => {
                        let var = operation[1];
                        let pos: usize = var.parse().unwrap();
                        let num = st[stack_pointer - 1];
                        stack_pointer -= 1;
                        memory[pos] = num;
                    }
                    "CJP" => {
                        let var = operation[1];
                        let pos: usize = var.parse().unwrap();
                        if st[stack_pointer] == 0 {
                            prog_counter = pos;
                        }
                    }
                    "UJP" => {
                        let var = operation[1];
                        let pos: usize = var.parse().unwrap();
                        prog_counter = pos;
                    }
                    _ => {
                        panic!("Invalid Instruction Code")
                    }
                }
            }
            _ => {
                panic!("Invalid Operators");
            }
        }
        prog_counter += 1;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_normal_add() {
        let mut buf: Vec<u8> = Vec::new();
        let operators: Vec<String> = vec![
            "LDC 5".to_string(),
            "STR 0".to_string(),
            "LOD 0".to_string(),
            "LDC 10".to_string(),
            "ADD".to_string(),
            "STR 0".to_string(),
            "PUT 0".to_string(),
        ];
        process(&mut buf, &operators);
        assert_eq!(buf, b"15\n");
    }

    #[test]
    fn test_normal_sub() {
        let mut buf: Vec<u8> = Vec::new();
        let operators: Vec<String> = vec![
            "LDC 5".to_string(),
            "STR 0".to_string(),
            "LOD 0".to_string(),
            "LDC 10".to_string(),
            "SUB".to_string(),
            "STR 0".to_string(),
            "PUT 0".to_string(),
        ];
        process(&mut buf, &operators);
        assert_eq!(buf, b"-5\n");
    }

    #[test]
    fn test_normal_mlt() {
        let mut buf: Vec<u8> = Vec::new();
        let operators: Vec<String> = vec![
            "LDC 5".to_string(),
            "STR 0".to_string(),
            "LOD 0".to_string(),
            "LDC 10".to_string(),
            "MLT".to_string(),
            "STR 0".to_string(),
            "PUT 0".to_string(),
        ];
        process(&mut buf, &operators);
        assert_eq!(buf, b"50\n");
    }

    #[test]
    fn test_normal_div() {
        let mut buf: Vec<u8> = Vec::new();
        let operators: Vec<String> = vec![
            "LDC 5".to_string(),
            "STR 0".to_string(),
            "LOD 0".to_string(),
            "LDC 2".to_string(),
            "DIV".to_string(),
            "STR 0".to_string(),
            "PUT 0".to_string(),
        ];
        process(&mut buf, &operators);
        assert_eq!(buf, b"2\n");
    }

    #[test]
    fn test_normal_sample2() {
        let mut buf: Vec<u8> = Vec::new();
        let operators: Vec<String> = vec![
            "LDC 3".to_string(),
            "STR 11".to_string(),
            "LDC 0".to_string(),
            "STR 0".to_string(),
            "LDC 1".to_string(),
            "STR 10".to_string(),
            "LOD 10".to_string(),
            "LOD 11".to_string(),
            "LDC 1".to_string(),
            "ADD".to_string(),
            "LET".to_string(),
            "CJP 20".to_string(),
            "LOD 0".to_string(),
            "LOD 10".to_string(),
            "ADD".to_string(),
            "STR 0".to_string(),
            "LOD 10".to_string(),
            "LDC 1".to_string(),
            "ADD".to_string(),
            "STR 10".to_string(),
            "UJP 5".to_string(),
            "PUT 0".to_string(),
        ];
        process(&mut buf, &operators);
        assert_eq!(buf, b"6\n");
    }
}
