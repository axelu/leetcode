
// 2620. Counter
// https://leetcode.com/problems/counter/



/**
 * @param {number} n
 * @return {Function} counter
 */
var createCounter = function(n) {
    var _n = n;
    return function() {
        var t = _n;
        ++_n;
        return t;
    };
};

/**
 * const counter = createCounter(10)
 * counter() // 10
 * counter() // 11
 * counter() // 12
 */
