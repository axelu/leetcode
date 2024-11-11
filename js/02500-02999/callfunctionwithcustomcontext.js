
// 2693. Call Function with Custom Context
// https://leetcode.com/problems/call-function-with-custom-context/




/**
 * @param {Object} context
 * @param {Array} args
 * @return {null|boolean|number|string|Array|Object}
 */
Function.prototype.callPolyfill = function(context, ...args) {
    const f = this;

    // solving with using the built-in Function.call method
    // return f.call(context, ...args);
    // but problem asks to solve this without using the built-in Function.call method

    const boundedf = f.bind(context);
    return boundedf(...args);


}

/**
 * function increment() { this.count++; return this.count; }
 * increment.callPolyfill({count: 1}); // 2
 */
