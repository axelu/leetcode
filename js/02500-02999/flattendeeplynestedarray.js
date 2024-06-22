
// 2625. Flatten Deeply Nested Array
// https://leetcode.com/problems/flatten-deeply-nested-array/






/**
 * @param {Array} arr
 * @param {number} depth
 * @return {Array}
 */
var flat = function (arr, n) {
    // return arr.flat(n);
    // per problem statement: solve it without the built-in Array.flat method

    return rec(arr, 0, n);
};

function rec(arr, depth, n) {
    if( depth == n )
        return arr;

    let ret = new Array();

    for(let i = 0; i < arr.length; ++i) {
        if( Array.isArray(arr[i]) ) {
            let t = rec(arr[i], depth + 1, n);
            if( t.length > 0 )
                ret.push(...t);
        } else {
            ret.push(arr[i]);
        }
    }

    return ret;
}
