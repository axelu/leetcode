
// 2623. Memoize
// https://leetcode.com/problems/memoize/







/**
 * @param {Function} fn
 * @return {Function}
 */
function memoize(fn) {

    let mem = new Map();

    return function(...args) {

        let key = args.toString();
        if( mem.has(key) )
            return mem.get(key);

        let t = fn(...args);

        mem.set(key, t);
        return t;
    }
}


/**
 * let callCount = 0;
 * const memoizedFn = memoize(function (a, b) {
 *	 callCount += 1;
 *   return a + b;
 * })
 * memoizedFn(2, 3) // 5
 * memoizedFn(2, 3) // 5
 * console.log(callCount) // 1
 */
