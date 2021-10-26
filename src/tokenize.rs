use super::error::CompilationError;

#[derive(Debug, PartialEq, Eq)]
enum TokenKind {
    Symbol,
    Number,
    Identifier,
    Read,
    Write,
    While,
    Do,
    EndWhile,
}

#[derive(Debug, PartialEq, Eq)]
pub struct Token {
    kind: TokenKind,
    val: i32,
    text: String,
}

impl Token {
    fn new(kind: TokenKind, val: i32, text: String) -> Token {
        Token { kind, val, text }
    }
}

pub struct Tokenizer {}

impl Tokenizer {
    pub fn new() -> Tokenizer {
        Tokenizer {}
    }

    pub fn tokenize(&self, input: String) -> Result<Vec<Token>, Box<dyn std::error::Error>> {
        let mut tokens: Vec<Token> = Vec::new();
        let split_input: Vec<&str> = input.split_whitespace().collect();
        for s in split_input {
            let cs: Vec<char> = s.chars().collect();
            let mut i = 0;
            while i < cs.len() {
                // Assign
                if cs[i] == ':' {
                    if i >= cs.len() || cs[i + 1] != '=' {}
                    let tk = Token::new(TokenKind::Symbol, -1, String::from(":="));
                    tokens.push(tk);
                    i += 2;
                    continue;
                }
                // Symbols
                if cs[i] == '.'
                    || cs[i] == ';'
                    || cs[i] == '<'
                    || cs[i] == '='
                    || cs[i] == '>'
                    || cs[i] == '+'
                    || cs[i] == '-'
                    || cs[i] == '*'
                    || cs[i] == '/'
                    || cs[i] == '('
                    || cs[i] == ')'
                {
                    let tk = Token::new(TokenKind::Symbol, -1, cs[i].to_string());
                    tokens.push(tk);
                    i += 1;
                    continue;
                }
                // READ
                if cs[i] == 'R' && i <= cs.len() - 4 {
                    let target: String = cs[i..i + 4].iter().collect();
                    if target == "READ" {
                        let tk = Token::new(TokenKind::Read, -1, target);
                        tokens.push(tk);
                        i += 4;
                        continue;
                    }
                }
                // WRITE | WHILE
                if cs[i] == 'W' && i <= cs.len() - 5 {
                    let target: String = cs[i..i + 5].iter().collect();
                    if target == "WRITE" {
                        let tk = Token::new(TokenKind::Write, -1, target);
                        tokens.push(tk);
                        i += 5;
                        continue;
                    }
                    if target == "WHILE" {
                        let tk = Token::new(TokenKind::While, -1, target);
                        tokens.push(tk);
                        i += 5;
                        continue;
                    }
                }
                // DO
                if cs[i] == 'D' && i <= cs.len() - 2 {
                    let target: String = cs[i..i + 2].iter().collect();
                    if target == "DO" {
                        let tk = Token::new(TokenKind::Do, -1, target);
                        tokens.push(tk);
                        i += 2;
                        continue;
                    }
                }
                // ENDWHILE
                if cs[i] == 'E' && i <= cs.len() - 8 {
                    let target: String = cs[i..i + 8].iter().collect();
                    if target == "ENDWHILE" {
                        let tk = Token::new(TokenKind::EndWhile, -1, target);
                        tokens.push(tk);
                        i += 8;
                        continue;
                    }
                }
                // Identifier
                if cs[i] >= 'A' && cs[i] <= 'Z' {
                    let tk = Token::new(TokenKind::Identifier, -1, cs[i].to_string());
                    tokens.push(tk);
                    i += 1;
                    continue;
                }
                // Number
                if cs[i].is_digit(10) {
                    let mut num = cs[i] as i32 - 48; // convert to i32
                    let mut num_string = cs[i].to_string();
                    i += 1;
                    while i < cs.len() && cs[i].is_digit(10) {
                        let n = cs[i] as i32 - 48;
                        num *= 10;
                        num += n;
                        num_string.push(cs[i]);
                        i += 1;
                    }
                    let tk = Token::new(TokenKind::Number, num, num_string);
                    tokens.push(tk);
                    continue;
                }
                return Err(Box::new(CompilationError::UnknownTokenError(
                    cs[i..].iter().collect(),
                )));
            }
        }

        Ok(tokens)
    }
}

#[allow(unused_macros)]
macro_rules! test_set {
    ($name:ident, $arg:expr, $want:expr) => {
        #[test]
        fn $name() {
            let tokenizer = Tokenizer {};
            let got = tokenizer.tokenize(String::from($arg));
            assert_eq!(got.unwrap(), $want);
        }
    };
}

#[cfg(test)]
mod tests {
    use super::*;

    test_set!(
        symbol_assign,
        ":=",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from(":=")
        }]
    );
    test_set!(
        symbol_dot,
        ".",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from(".")
        }]
    );
    test_set!(
        symbol_semicolon,
        ";",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from(";")
        }]
    );
    test_set!(
        symbol_less,
        "<",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from("<")
        }]
    );
    test_set!(
        symbol_equal,
        "=",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from("=")
        }]
    );
    test_set!(
        symbol_greater,
        ">",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from(">")
        }]
    );
    test_set!(
        symbol_plus,
        "+",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from("+")
        }]
    );
    test_set!(
        symbol_minus,
        "-",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from("-")
        }]
    );
    test_set!(
        symbol_multiple,
        "*",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from("*")
        }]
    );
    test_set!(
        symbol_div,
        "/",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from("/")
        }]
    );
    test_set!(
        symbol_left_paren,
        "(",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from("(")
        }]
    );
    test_set!(
        symbol_right_paren,
        ")",
        vec![Token {
            kind: TokenKind::Symbol,
            val: -1,
            text: String::from(")")
        }]
    );
    test_set!(
        reserved_read,
        "READ",
        vec![Token {
            kind: TokenKind::Read,
            val: -1,
            text: String::from("READ")
        }]
    );
    test_set!(
        reserved_write,
        "WRITE",
        vec![Token {
            kind: TokenKind::Write,
            val: -1,
            text: String::from("WRITE")
        }]
    );
    test_set!(
        reserved_while,
        "WHILE",
        vec![Token {
            kind: TokenKind::While,
            val: -1,
            text: String::from("WHILE")
        }]
    );
    test_set!(
        reserved_do,
        "DO",
        vec![Token {
            kind: TokenKind::Do,
            val: -1,
            text: String::from("DO")
        }]
    );
    test_set!(
        reserved_endwhile,
        "ENDWHILE",
        vec![Token {
            kind: TokenKind::EndWhile,
            val: -1,
            text: String::from("ENDWHILE")
        }]
    );
    test_set!(
        reserved_ident_a,
        "A",
        vec![Token {
            kind: TokenKind::Identifier,
            val: -1,
            text: String::from("A")
        }]
    );
    test_set!(
        reserved_ident_z,
        "Z",
        vec![Token {
            kind: TokenKind::Identifier,
            val: -1,
            text: String::from("Z")
        }]
    );
    test_set!(
        num_largest,
        "32767",
        vec![Token {
            kind: TokenKind::Number,
            val: 32767,
            text: String::from("32767")
        }]
    );
    test_set!(
        num_smallest,
        "-32768",
        vec![
            Token {
                kind: TokenKind::Symbol,
                val: -1,
                text: String::from("-")
            },
            Token {
                kind: TokenKind::Number,
                val: 32768,
                text: String::from("32768")
            }
        ]
    );
    test_set!(
        success_with_whitespace,
        "  (*
35",
        vec![
            Token {
                kind: TokenKind::Symbol,
                val: -1,
                text: String::from("(")
            },
            Token {
                kind: TokenKind::Symbol,
                val: -1,
                text: String::from("*")
            },
            Token {
                kind: TokenKind::Number,
                val: 35,
                text: String::from("35")
            }
        ]
    );
    test_set!(no_input, "", vec![]);
    #[test]
    fn fail() {
        let tokenizer = Tokenizer {};
        let got = tokenizer.tokenize(String::from("-&+"));
        assert!(got.unwrap_err().is::<CompilationError>());
    }
}
