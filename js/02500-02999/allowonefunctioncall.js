
// 2666. Allow One Function Call
// https://leetcode.com/problems/allow-one-function-call/




/**
 * @param {Function} fn
 * @return {Function}
 */
var once = function(fn) {
    let has_run = 0;
    return function(...args){
        if( has_run == 0 ) {
            has_run = 1;
            return fn.apply(this, args);
        }
    }
};

/**
 * let fn = (a,b,c) => (a + b + c)
 * let onceFn = once(fn)
 *
 * onceFn(1,2,3); // 6
 * onceFn(2,3,6); // returns undefined without calling fn
 */

