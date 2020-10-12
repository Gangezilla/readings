// Simple Hangman Program
// User gets five incorrect guesses
// Word chosen randomly from words.txt
// Inspiration from: https://doc.rust-lang.org/book/ch02-00-guessing-game-tutorial.html
// This assignment will introduce you to some fundamental syntax in Rust:
// - variable declaration
// - string manipulation
// - conditional statements
// - loops
// - vectors
// - files
// - user input
// We've tried to limit/hide Rust's quirks since we'll discuss those details
// more in depth in the coming lectures.
extern crate rand;
use rand::Rng;
use std::fs;
use std::io;
use std::io::Write;

const NUM_INCORRECT_GUESSES: u32 = 5;
const WORDS_PATH: &str = "words.txt";

fn pick_a_random_word() -> String {
    let file_string = fs::read_to_string(WORDS_PATH).expect("Unable to read file.");
    let words: Vec<&str> = file_string.split('\n').collect();
    String::from(words[rand::thread_rng().gen_range(0, words.len())].trim())
}

fn format_guess(guess_count: u32) -> String {
    if guess_count > 1 {
        return "guesses".to_string();
    } else {
        return "guess".to_string();
    }
}

fn validate_guess(guess: &String, secret_word_chars: &Vec<char>) -> bool {
    let mut is_char_in_word: bool = false;
    for letter in secret_word_chars {
        if *letter == guess.chars().nth(0).unwrap() {
            is_char_in_word = true;
        }
    }
    is_char_in_word
}

fn format_secret_word(guessed_chars: &Vec<char>, secret_word_chars: &Vec<char>) -> String {
    // O(n^2) but whatever
    let mut formatted_word: Vec<String> = secret_word_chars.to_vec()
    for letter in formatted_word {
        for guessed_char in guessed_chars {
            if *letter == *guessed_char {

            } else {

            }
        }
    }
    // we could copy the whole word into a new vector
    // loop over that new vector and see if the character exists in guessed chars
    // if it doesnt, replace it with a -

    // let mut found = false;
    // for secret_letter in secret_word_chars {
    //     for guessed_char in guessed_chars {
    //         if *secret_letter == *guessed_char {
    //             found = true;
    //         } else {
    //             found = false;
    //         }
    //     }
    //     if found {
    //         formatted_word.push(secret_letter.to_string())
    //     } else {
    //         formatted_word.push("-".to_string())
    //     }
    // }
    // formatted_word.join("")
}

fn main() {
    let secret_word = pick_a_random_word();
    let secret_word_chars: Vec<char> = secret_word.chars().collect();
    let mut guessed_chars: Vec<char> = Vec::new();
    let mut guess_count = NUM_INCORRECT_GUESSES;
    let mut correct_guess_count = 0;
    
    // Uncomment for debugging:
    println!("random word: {}", secret_word);
    println!("Welcome to CS110L Hangman!");

    fn ask_for_input() {
        
    }

    loop {
        let formatted_secret_word = format_secret_word(&guessed_chars, &secret_word_chars);
        println!("The word so far is {}", formatted_secret_word);
        println!("You have guessed the following letters: {:?}", guessed_chars);
        println!("You have {} {} left", guess_count, format_guess(guess_count));
        print!("Please guess a letter: ");
        match io::stdout().flush() {
            Ok(_) => (),
            Err(_) => (),
        };

        let mut guess = String::new();
        // Validate that we've only received a char, not multiple.
            // if multiple, reprompt. maybe just worry about happy path for now. 
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        
        let is_valid_guess = validate_guess(&guess, &secret_word_chars);
        guessed_chars.push(guess.chars().nth(0).unwrap());

        println!();

        if is_valid_guess {
            if correct_guess_count == secret_word_chars.len() {
                println!("Congratulations, you guessed the secret word: {}!", formatted_secret_word);
                std::process::exit(0);
            } else {
                correct_guess_count += 1;
            }
        } else {
            println!("Sorry, that letter is not in the word");
            if guess_count == 0 {
                println!("Sorry, you ran out of guesses!");
                std::process::exit(0);
            } else {
                guess_count -= 1;
            }
        }

    }
    // gameplay loop
        // take users input
        // see if the char theyve given us is in the vector
        // if it is, show success, if not show fail
    // needed datastructures
    // guess count
    // guessed letters
    // 
}
