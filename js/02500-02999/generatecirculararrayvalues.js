
// 2757. Generate Circular Array Values
// https://leetcode.com/problems/generate-circular-array-values/




/**
 * @param {Array<number>} arr
 * @param {number} startIndex
 * @yields {number}
 */
var cycleGenerator = function* (arr, startIndex) {
    let n = arr.length;
    let idx = startIndex;

    let jump = 0;
    do {
        // console.log("before " + jump);
        if( jump > 0 ) {
            idx = (idx + jump) % n;
        } else if( jump < 0 ) {
            jump = (-1 * jump) % n;
            idx = idx - jump;
            if( idx < 0 )
                idx += n;
        }
        jump = yield arr[idx];
    }while(true);
};

/**
 *  const gen = cycleGenerator([1,2,3,4,5], 0);
 *  gen.next().value  // 1
 *  gen.next(1).value // 2
 *  gen.next(2).value // 4
 *  gen.next(6).value // 5
 */
