
// 2724. Sort By
// https://leetcode.com/problems/sort-by/





/**
 * @param {Array} arr
 * @param {Function} fn
 * @return {Array}
 */
var sortBy = function(arr, fn) {

    function compareFn(a, b) {
        let aval = fn(a);
        let bval = fn(b);
        if( aval < bval ) {
            return -1;
        } else if( aval > bval ) {
            return 1;
        }
        return 0;
    }

    arr.sort(compareFn);
    return arr;
};
