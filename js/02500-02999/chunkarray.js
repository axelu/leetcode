
// 2677. Chunk Array
// https://leetcode.com/problems/chunk-array/




/**
 * @param {Array} arr
 * @param {number} size
 * @return {Array[]}
 */
var chunk = function(arr, size) {
    const ret = [];
    for(let i = 0; i < arr.length;) {
        const inner = [];
        let j = i;
        for(; j < i + size && j < arr.length; ++j) {
            inner.push(arr[j]);
        }
        ret.push(inner);
        i = j;
    }
    return ret;
};
