// I imagine the BCR (best conceivable runtime cos i always forget it) would be O(n) because we have to go through the whole string to compress it.
// anyway, i imagine we can run through the string, comparing the next char and if it's not the same, pushing whatever the count is to the other string.
// we can also keep a flag at the start to know if a string isn't compressable, which we can flip as soon as we encounter something to compress.

// stringCompressionConcatString: 2.1484450101852417ms milliseconds.
// stringCompressionJoinArray: 0.4435979127883911ms milliseconds.
// stringCompressionConcatMethod: 0.09398496150970459ms milliseconds.
// so doing this as an array and joining it is WAY quicker than doing it the concat way.
// however, doing it with the actual String.concat method is quicker still. interesting.

const { performance } = require('perf_hooks');

const stringCompressionConcatString = (str) => {
  let compressedStr = '';
  let currentCount = 1;
  let currentChar = '';
  let isCompressable = false;

  for (let i = 0; i < str.length; i++) {
    currentChar = str[i];
    if (currentChar === str[i + 1]) {
      isCompressable = true; // flipping this multiple times, bit redundant
      currentCount += 1;
    } else {
      compressedStr += `${currentChar}${currentCount}`;
      currentCount = 1;
    }
  }
  if (isCompressable) {
    return compressedStr;
  } else {
    return str;
  }
}

const stringCompressionJoinArray = (str) => {
  let compressedStrParts = [];
  let currentCount = 1;
  let currentChar = '';
  let isCompressable = false;

  for (let i = 0; i < str.length; i++) {
    currentChar = str[i];
    if (currentChar === str[i + 1]) {
      isCompressable = true; // flipping this multiple times, bit redundant
      currentCount += 1;
    } else {
      compressedStrParts.push(`${currentChar}${currentCount}`);
      currentCount = 1;
    }
  }
  if (isCompressable) {
    const joinedStr = compressedStrParts.join('');
    return joinedStr;
  } else {
    return str;
  }
}

const stringCompressionConcatMethod = (str) => {
  let compressedStr = '';
  let currentCount = 1;
  let currentChar = '';
  let isCompressable = false;

  for (let i = 0; i < str.length; i++) {
    currentChar = str[i];
    if (currentChar === str[i + 1]) {
      isCompressable = true; // flipping this multiple times, bit redundant
      currentCount += 1;
    } else {
      compressedStr.concat(`${currentChar}${currentCount}`);
      currentCount = 1;
    }
  }
  if (isCompressable) {
    return compressedStr;
  } else {
    return str;
  }
}

(function () {
  const t0 = performance.now();
  stringCompressionConcatString('aabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaa');
  const t1 = performance.now();

  const t2 = performance.now();
  stringCompressionJoinArray('aabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaa')
  const t3 = performance.now();

  const t4 = performance.now();
  stringCompressionConcatMethod('aabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaaaabcccccaaa')
  const t5 = performance.now();

  console.log(`stringCompressionConcatString: ${(t1 - t0)}ms` + " milliseconds.");
  console.log(`stringCompressionJoinArray: ${(t3 - t2)}ms` + " milliseconds.");
  console.log(`stringCompressionConcatMethod: ${(t5 - t4)}ms` + " milliseconds.");
})();
