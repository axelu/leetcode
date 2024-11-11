
// 2624. Snail Traversal
// https://leetcode.com/problems/snail-traversal/




/**
 * @param {number} rowsCount
 * @param {number} colsCount
 * @return {Array<Array<number>>}
 */
Array.prototype.snail = function(rowsCount, colsCount) {
    const nums = this;
    const n = nums.length;
    if( rowsCount * colsCount !== n )
        return [];

    const arr = new Array();
    for(let i = 0; i < rowsCount; ++i) {
        const row = new Array(colsCount);
        arr.push(row);
    }

    for(let k = 0; k < n; ++k) {    // index in nums
        const j = Math.floor(k / rowsCount);    // col
        let i = k % rowsCount;                  // row
        if( j % 2 )
            i = (rowsCount - 1) - i;
        arr[i][j] = nums[k];
    }

    return arr;
}

/**
 * const arr = [1,2,3,4];
 * arr.snail(1,4); // [[1,2,3,4]]
 */
