# Chapter 2
In order to compare algorithms, we need techniques that enable us to compare the efficiency of algorithms without implementing them. Our two most important tools are the RAM (Random Access Machine) model of computation, and asymptotic analysis of worst-case complexity

## The RAM Model of Computation
The RAM Model of Computation depends upon a hypothetical computer called the Random Access Machine or RAM, which gives us a computer where:
- Each simple operation (+ * - = if call) take one time step
- Loops and subroutines are not simple operations, they are the composition of many single-step operations. The time it takes to run through a loop or execute a subprogram depends upon the number of loop iterations or the specific nature of the subprogram.
- Each memory access takes exactly one time step.

Under the RAM model, we measure time by counting the number of steps an algo takes. Assuming our RAM executes a given number of steps per second, this operation count converts naturally to the actual running time. This is a simplified model, but it gives us an excellent model for understanding how an algo will actually perform. It allows us to understand and study algos in a language and machine independent manner.

### Best, worst and average case complexity.
To understand an algo, we must know how it works at the top, middle and in general cases.
- The worst case complexity of an algo is defined by the maximum number of steps taken in any instance. (sorting algo, completely unordered)
- The best case complexity is the minimum number of steps taken in any instance (sorting algo, already ordered)
- The average case complexity, which is the average number of steps (sorting algo, half ordered)
The worst case complexity proves to be the most useful of these three measures in practice. Time complexities are so complicated that we must simplify them to work with them, so we use "Big Oh" notation.

## Big Oh Notation
Best worst and average case complexities are difficult to work with precisely, because functions:
- Have too many bumps - for example, an algo like binary search runs faster on arrays of a particular size because the array partitions work out nicely. This isn't too significant but it warns us that the exact complexity for any algorithm is liable to be complicated, with little up and down bumps
- Require too much detail to specify precisely - Counting the exact number of instructions in worst case requires the algo be specified to the detail of a complete program. This is difficult and doesn't give us too much extra info than the statement "the time grows quadratically with n"

It's easier to just talk in terms of simple upper and lower bounds of time-complexity functions. The Big Oh simplifies our analysis by ignoring levels of detail that don't impact our comparison of algorithms. Big Oh enables us to ignore details and focus on the big picture.

Big Oh notation and worst-case analysis are tools that greatly simplify our ability to compare the efficiency of algorithms

## Growth Rates and Dominance Relations
With Big Oh we discard multiplicative constants, so f(n) = 0.001n^2 and g(n) = 1000n2 are treated identically, even though g(n) is way larger. We do this because of the growth rate or having much higher numbers, and that ignoring constant factors we still get an excellent idea of whether a given algorithm is appropriate for a problem of a given size. There's a few things we can get from a table included on p38:
- Any algo with n! running time becomes useless for n >= 20
- Quadratic time algos whose running time is n^2 remain usable up to n = 10000 but deteriorate with larger inputs.
- An O(lg n) algo hardly breaks a sweat for any imaginable value of n
- Linear time and n lg n algos remain practical on inputs of a billion items.

### Dominance Relations
We say that a faster-growing function dominates a slower-growing one. Big Oh notation groups function into a set of classes, such that all functions in a particular class are equivalent with respect to the Big Oh. There's only a few function classes that tend to crop up, and these go in order of increasing dominance (because they grow faster and thus are slower)
- Constant functions, f(n) = 1 - For example, measuring the cost of adding two numbers, printing out a string. In the big picture, there's no dependence on the parameter n.
- Logarithmic functions f(n) = log n - Logarithmic time-complexity shows up in algorithms such as binary search. This grows quite slowly as n gets big, but faster than the constant function.
- Linear functions, f(n) = n - Such functions measure  the cost of looking at each item once (or twice or ten  times) in an n-element array, say, to identify the biggest item. Linear because you're always going to have to go through the whole array.
- Superlinear functions, f(n) = n lg n - They grow just a little faster than linear, used in algos like quicksort and merge sort.
- Quadratic functions, f(n) = n^2 - such functions measure the cost of looking at most or all pairs of items in an n-element universe. This arises in algos like insertion sort and selection sort.
- Cubic functions, f(n) = n^3, such functions enumerate through all triples of items.
- Exponential functions, f(n) = c^n for a given constant c > 1 - Functions like 2^n arise when enumerating all subsets of n items. These become useless really quickly.
- Factorial functions, f(n) = n! - Functions like n! arise when generating all permutations or orderings of n items.

Although esoteric functions arise in advanced algo analysis, a small variety of time complexities suffice and account for most algos that are widely used.

## Working with Big Oh
### Adding Functions
- The sum of two functions is governed by the dominant one. This is good for simplification, as it means n^3 + n^2 + n + 1 = O(n^3). Everything but the most dominant term is insignificant.

## Reasoning About Efficiency
### Selection Sort
Selectio sort repeatedlty identifies the smallest remaining unsorted element and puts it at the end of the sorted portion of  the array.

## Logarithms and their Applications
A logarithm is simply an inverse exponential function. Saying b^x = y is equivalent to saying that x = log▼b y. Whereas exponential functions grow at a very fast rate, inverse exponential (or logarithmic) functions grow really slowly. Logarithms arise in any process where things are repeatedly halved.
### Logarithms and Binary Search
Binary  search is a good example of an O(log n) algorithm. To locate a particular person in a telephone book, you open it in half, and then continuing opening progressive halves until you've found what you're after. The number of steps the algorithm takes equals the number of times we can halve n until only one name is left.
### Logarithms and Trees
The punch line is that very short trees can have very many leaves, which is the main reason why binary trees prove fundamental to the design of fast data structures.
### Logarithms and Multiplication
Logarithms were particularly important in the days before pocket calculators. They provided the easiest way to multiply big numbers by hand.

Logarithms arise whenever things are repeatedly halved or doubled.

## Properties of Logarithms
As we've seen, stating b^x = y is equivalent to saying x = log▼b y. The b term is known as the base of the logarithm. Three bases are important:
- Base b = 2 - the binary logarithm, usually denoted lg x is a base 2 logarithm. We've seen how this base arises whenever repeated halving or doubling occurs. Most algorithmic applications of logarithms imply binary logarithms.
- Base b = e - The natural log, usually denoted ln x, is a base e logarithm. The inverse of ln x is the exponential function.
- Base b = 10 - less common today is the base 10 or common logarithm.
It's easy to convert one form of logarithm to another.
