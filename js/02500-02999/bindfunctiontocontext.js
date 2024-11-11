
// 2754. Bind Function to Context
// https://leetcode.com/problems/bind-function-to-context/




/**
 * @param {Object} obj
 * @return {Function}
 */
Function.prototype.bindPolyfill = function(obj) {
    const f = this;

    return function(...args) {
        return f.apply(obj, args); // return result of executing the function
    }
}
