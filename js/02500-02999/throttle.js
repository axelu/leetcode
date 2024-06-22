
// 2676. Throttle
// https://leetcode.com/problems/throttle/






/**
 * @param {Function} fn
 * @param {number} t
 * @return {Function}
 */
var throttle = function(fn, t) {

    let next = 0;
    let timeoutID = -1;

    return function(...args) {
        let d = Math.max(0, next - Date.now());
        clearTimeout(timeoutID);
        timeoutID = setTimeout(() => {
            fn(...args);
            next = Date.now() + t;
        }, d);
    }
};

/**
 * const throttled = throttle(console.log, 100);
 * throttled("log"); // logged immediately.
 * throttled("log"); // logged at t=100ms.
 */
