// If we have a matrix that looks like this:
// [
//   ['abcd', 'efgh', 'ijkl'],
//   ['mnop', 'qrst', 'uvwx'],
//   ['yzab', 'cdef', 'ghij']
// ]
// we need it to look like this:
// [
//   ['ijkl', 'uvwx', 'ghij'],
//   ['efgh', 'qrst', 'cdef'],
//   ['abcd', 'mnop', 'yzab'],
// ]
// the easiest way (i think) is to essentially grab each column and make that into a new row
// and with each new row, we add that onto the front of the array
// my solution still lands us at an O(n^2) because we have to go through each element in a nested loop.
// so i've assumed that it's already partitioned. what if it isn't?
// can we do it any quicker?


// it's a bit different from the solution, because i've rotated mine -90 degrees, instead of 90 degres.

// but in saying that, positive 90 degrees is just pushing each new row to the back instead of the front, so we can add a flag in to make it more extensible.

const rotateMatrixNegative90 = (matrix, direction = 'left') => {
  const matrixLength = matrix[0].length;
  const rotatedMatrix = [];
  for (let i = 0; i < matrixLength; i++) {
    const newRow = [];
    for (let j = 0; j < matrixLength; j++) {
      newRow.push(matrix[j][i]);
    }
    if (direction === 'left') {
      rotatedMatrix.unshift(newRow);
    } else {
      rotatedMatrix.push(newRow);
    }
  }
  console.log(rotatedMatrix);
  return rotatedMatrix;
}

(() => {
  rotateMatrixNegative90([
    ['abcd', 'efgh', 'ijkl'],
    ['mnop', 'qrst', 'uvwx'],
    ['yzab', 'cdef', 'ghij']
  ], 'left');

  rotateMatrixNegative90([
    ['abcd', 'efgh', 'ijkl'],
    ['mnop', 'qrst', 'uvwx'],
    ['yzab', 'cdef', 'ghij']
  ], 'right');

  rotateMatrixNegative90([
    ['abcd', 'efgh', 'ijkl'],
    ['mnop', 'qrst', 'uvwx'],
    ['yzab', 'cdef', 'ghij']
  ], 'right');
})();
