// Unless I'm missing something, this is pretty easy with the built in String.replace method.
// I think this would always be o(N) as best conceivable runtime (BCR)

const urlify = string => string.replace(/\s/g, '%20');
