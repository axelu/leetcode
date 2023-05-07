
// 2634. Filter Elements from Array
// https://leetcode.com/problems/filter-elements-from-array/




/**
 * @param {number[]} arr
 * @param {Function} fn
 * @return {number[]}
 */
var filter = function(arr, fn) {
    const ret = [];
    for(var i = 0; i < arr.length; ++i)
        if( fn(arr[i],i) )
            ret.push(arr[i]);
    return ret;
};
