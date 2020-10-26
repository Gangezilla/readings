use std::env;
use std::process;
use std::fs::File; // For read_file_lines()
use std::io::{self, BufRead}; // For read_file_lines()

/// Reads the file at the supplied path, and returns a vector of strings.
fn read_file_lines(filename: &String) -> Result<Vec<String>, io::Error> {
    let mut lines = Vec::new();
    let file = match File::open(filename) {
        Ok(file) => file,
        Err(err) => return Err(err),
    };

    for line in io::BufReader::new(file).lines() {
        match line {
            Ok(text) => lines.push(text),
            Err(err) => return Err(err),
        };
    }
    Ok(lines)
}

fn get_rest(lines: &Vec<String>) -> (usize, usize) {
    let mut word_count: usize = 0;
    let mut char_count: usize = 0;

    for line in lines {
        char_count += line.chars().count();
        let words: Vec<&str> = line.split_whitespace().collect();
        word_count += words.len();
    }
    
    (word_count, char_count)
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Too few arguments.");
        process::exit(1);
    }
    let filename = &args[1];
    let lines = read_file_lines(filename).expect("Filename is invalid");
    let line_count = lines.len();

    let (word_count, char_count) = get_rest(&lines);
    println!("       {}       {}       {} {}", line_count, word_count, char_count, filename);
}
