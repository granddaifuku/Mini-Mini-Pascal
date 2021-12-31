use std::io::Write;

#[allow(unused_mut)]
pub fn process<W: Write>(writer: &mut W, operations: &Vec<String>) {
    let mut st: Vec<i32> = Vec::new();
    let mut memory: [i32; 26] = [0; 26];
    let mut stack_pointer = 0;
    let mut prog_counter = 0;

    // Split with the blank
    while prog_counter < operations.len() {
        let operation: Vec<&str> = operations[prog_counter].split_whitespace().collect();
        match operation.len() {
            1 => match operation[0] {
                "ADD" => {
                    let a = st.pop().unwrap();
                    let b = st.pop().unwrap();
                    st.push(a + b);
                    stack_pointer -= 1;
                }
                "SUB" => {
                    let a = st.pop().unwrap();
                    let b = st.pop().unwrap();
                    st.push(b - a);
                    stack_pointer -= 1;
                }
                "MLT" => {
                    let a = st.pop().unwrap();
                    let b = st.pop().unwrap();
                    st.push(a * b);
                    stack_pointer -= 1;
                }
                "DIV" => {
                    let a = st.pop().unwrap();
                    let b = st.pop().unwrap();
                    st.push(b / a);
                    stack_pointer -= 1;
                }
                "EQL" => {
                    let a = st.pop().unwrap();
                    let b = st.pop().unwrap();
                    stack_pointer -= 2;
                    if a == b {
                        st[stack_pointer as usize] = 1;
                    } else {
                        st[stack_pointer as usize] = 0;
                    }
                }
                "GRT" => {
                    let a = st.pop().unwrap();
                    let b = st.pop().unwrap();
                    stack_pointer -= 2;
                    if a < b {
                        st[stack_pointer as usize] = 1;
                    } else {
                        st[stack_pointer as usize] = 0;
                    }
                }
                "LET" => {
                    let a = st.pop().unwrap();
                    let b = st.pop().unwrap();
                    stack_pointer -= 2;
                    if a > b {
                        st[stack_pointer as usize] = 1;
                    } else {
                        st[stack_pointer as usize] = 0;
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
                        let pos = var.chars().nth(0).unwrap() as u32 - 'A' as u32;
                        // read std in
                        let mut s = String::new();
                        std::io::stdin().read_line(&mut s).unwrap();
                        memory[pos as usize] = s.parse().unwrap();
                    }
                    "PUT" => {
                        let var = operation[1];
                        let pos = var.chars().nth(0).unwrap() as u32 - 'A' as u32;
                        writeln!(writer, "{}", memory[pos as usize]).unwrap();
                    }
                    "LOD" => {
                        let var = operation[1];
                        let pos = var.chars().nth(0).unwrap() as u32 - 'A' as u32;
                        st.push(memory[pos as usize]);
                        stack_pointer += 1;
                    }
                    "LDC" => {
                        let var = operation[1];
                        let num = var.chars().nth(0).unwrap() as u32 - 'A' as u32;
                        st.push(num as i32);
                        stack_pointer += 1;
                    }
                    "STR" => {
                        let var = operation[1];
                        let pos = var.chars().nth(0).unwrap() as u32 - 'A' as u32;
                        let num = st.pop().unwrap();
                        stack_pointer -= 1;
                        memory[pos as usize] = num;
                    }
                    "CJP" => {
                        let var = operation[1];
                        let pos = var.chars().nth(0).unwrap() as u32 - 'A' as u32;
                        if st[stack_pointer as usize] == 0 {
                            prog_counter = pos as usize;
                        }
                    }
                    "UJP" => {
                        let var = operation[1];
                        let pos = var.chars().nth(0).unwrap() as u32 - 'A' as u32;
                        prog_counter = pos as usize;
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
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_normal() {
        let mut buf: Vec<u8> = Vec::new();
        let mut operators: Vec<String> = Vec::new();
        process(&mut buf, &operators);
    }
}
