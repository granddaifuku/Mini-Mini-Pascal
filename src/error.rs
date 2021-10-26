use std::{error, fmt};

#[derive(Debug)]
pub enum CompilationError {
    UnknownTokenError(String),
}

impl fmt::Display for CompilationError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        use self::CompilationError::*;
        match self {
            UnknownTokenError(s) => write!(f, "Unknown Token: {}", s),
        }
    }
}

impl error::Error for CompilationError {}
