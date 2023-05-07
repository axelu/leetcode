
// 2626. Array Reduce Transformation
// https://leetcode.com/problems/array-reduce-transformation/



/**
 * @param {number[]} nums
 * @param {Function} fn
 * @param {number} init
 * @return {number}
 */
var reduce = function(nums, fn, init) {
    let ret = init;
    for(let i = 0; i < nums.length; ++i)
        ret = fn(ret,nums[i]);
    return ret;
};
