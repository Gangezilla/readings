// isUnique: Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures ? - p102
// Inefficient way to do it would be to do a double loop and check if a character occurs multiple times.
// You could short circuit this to break if you hit the letter you're checking for, but you'll still be at 0(n ^ 2)
// I think a better way to do it would be to put each character into a dictionary

// Turns out that the 'slower' one runs faster until I use every character on my keyboard.
// However, the quickest way to do it is to do it using a Set.
// With the string below, we get an output like so:

// isUniqueSpeedier: 0.23025202751159668ms milliseconds.
// isUniqueSlower: 0.26908302307128906ms milliseconds.
// isUniqueSet: 0.1271580457687378ms milliseconds.

const { performance } = require('perf_hooks');

const isUniqueSlow = string => {
  for (let i = 0; i < string.length; i++) {
    for (let j = i + 1; j < string.length; j++) {
      if (string[i] === string[j]) {
        return false;
      }
    }
  }
  return true;
}

const isUniqueSpeedier = string => {
  const dict = {};
  for (let i = 0; i < string.length; i++) {
    const char = string[i];
    if (dict[char] === undefined) {
      dict[char] = true;
    } else {
      return false;
    }
  }
  return true;
}

const isUniqueSet = string => {
  const set = new Set(string);
  return set.size === string.length;
}

(function () {
  const speedier0 = performance.now();
  isUniqueSpeedier('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()`~-_=+[{]}\|;:\'",<.>/?');
  const speedier1 = performance.now();
  console.log(`isUniqueSpeedier: ${(speedier1 - speedier0)}ms` + " milliseconds.");

  const slower0 = performance.now();
  isUniqueSlow('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()`~-_=+[{]}\|;:\'",<.>/?');
  const slower1 = performance.now();
  console.log(`isUniqueSlower: ${(slower1 - slower0)}ms` + " milliseconds.");

  const set0 = performance.now();
  isUniqueSet('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()`~-_=+[{]}\|;:\'",<.>/?');
  const set1 = performance.now();
  console.log(`isUniqueSet: ${(set1 - set0)}ms` + " milliseconds.");
})();
