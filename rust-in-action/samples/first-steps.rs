fn main() { // you can put main wherever you want
    let a = 10; // types can be inferred from the compiler
    let b: i32 = 20; // or declared by the programmer when creating variables
    let c = 30i32; // numeric types can include a type annotation in their literal form
    let d = 30_i32; // underscores increase readability
    let e = add(add(a, b), add(c, d));
    println!("{}", e);

    fn add(i: i32, j: i32) -> i32 { // type declarations are required when defining functions
        i + j // functions return the last expressions result, meaning return is not required. BUT be careful as adding a semicolon would change the semantics to return () instead of i32
    }
}