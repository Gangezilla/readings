// checkPermutation: Given two strings, write a method to decide if one is a permutation of the other. - 102
// For example sake, lets say we have these:
// a: abbe
// b: cbabadcbbabbcbabaabccbabc
// well, what we could do would be generate all possible permutations of a string and see if it occurs in the array, which we could find using binary search. Binary search is O(log n), and finding all permutations is O(n!), so this would be O(n! log n) which seems pretty slow.
// hmm, well instead of generating all permutations, we could check it as we generate the permutation, which would at least bring us down to O(n!), but this could still take a super long time.
// we could first check if their lengths are the samd, if they're not, we know it's not a permutation
// why don't we sort stringA or stringB in place and see if they match.

const checkPermutation = (stringA, stringB) => {
  if (stringA.length !== stringB.length) {
    return false;
  } else {
    const sortedA = stringA.split('').sort().join('');
    const sortedB = stringB.split('').sort().join('');
    return sortedA === sortedB;
  }
}
