// Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palindrome. A palindrome is a word or phrase that is the same forwards and backwards. A permutation is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.

// so is this asking me to get a string, and  permutations of it, and check if that permutation is a palindrome?
// i think so.
// if a string has an even number of chars, then each character must appear an even number of times.
// if a string has an odd number of chars, then each character must appear an even number of times, with one char appearing an odd number of times.
// so going through the string and putting each char in a map is O(n). We'd then go over the object that we put all of our chars into, and check the count of each char, which would also be O(n). So this leaves us at O(2n)??

const palindromePermutation = (string) => {
  const charCount = {};
  let isPermutation = true;
  let secondChance = false;

  for (let i = 0; i < string.length; i++) {
    const char = string[i].toLowerCase();
    if (charCount[char] === undefined) {
      charCount[char] = 0;
    }
    charCount[char]++;
  }

  // could do it even quicker by doing this as a for loop and then exiting from the loop early if needed.
  Object.keys(charCount).forEach(char => {
    if (charCount[char] % 2 > 0) {
      if (secondChance) {
        isPermutation = false;
      } else {
        secondChance = true;
      }
    }
  })

  return isPermutation;
}

(function () {
  palindromePermutation('adfgadfg')
})();
