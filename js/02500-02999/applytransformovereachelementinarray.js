
// 2635. Apply Transform Over Each Element in Array
// https://leetcode.com/problems/apply-transform-over-each-element-in-array/



/**
 * @param {number[]} arr
 * @param {Function} fn
 * @return {number[]}
 */
var map = function(arr, fn) {
    const ret = [];
    for(var i = 0; i < arr.length; ++i)
        ret.push(fn(arr[i],i));
    return ret;
};
