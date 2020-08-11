fn main() {
    let context_lines = 2;
    let needle = "oo";
    let haystack = "Every face, every shop, bedroom window, public-house, and
    dark square is a picture feverishly turned--in search of what?
    It is the same with books. What do we seek through millions of pages?";

    let mut tags: Vec<usize> = Vec::new(); // tags holds line numbers where matches occur
    let mut ctx: Vec<Vec<(usize, String)>> = Vec::new();

    // first pass where we tag lines that match
    for (i, line) in haystack.lines().enumerate() {
        if line.contains(needle) {
            tags.push(i);

            let v = Vec::with_capacity(2 * context_lines + 1);
            ctx.push(v);
        }

        if tags.len() == 0 {
            return();
        }
    }

    // second pass where we collect lines within n lines of each of the tags
    for (i, line) in haystack.lines().enumerate() {
        for (j, tag) in tags.iter().enumerate() {
            let lower_bound = tag.saturating_sub(context_lines); // usize.saturating_sub() is subtraction that returns 0 on integer underflow rather than crash
            let upper_bound = tag + context_lines;

            if (i >= lower_bound) && (i <= upper_bound) {
                let line_as_string = String::from(line);
                let local_ctx = (i, line_as_string);
                ctx[j].push(local_ctx);
            }
        }
    }

    for local_ctx in ctx.iter() {
        for &(i, ref line) in local_ctx.iter() { // ref line informs the compiler we want to borrow this value
             let line_num = i + 1;
            println!("{}: {}", line_num, line);
        }
    }
    // let mut line_num: usize = 1;

    // for line in quote.lines() {
    //     if line.contains(search_term) {
    //         println!("{}", line);
    //     }
    // }
    // line_num += 1;
}
