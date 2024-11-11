
// 2776. Convert Callback Based Function to Promise Based Function
// https://leetcode.com/problems/convert-callback-based-function-to-promise-based-function/

// see also https://medium.com/codebuddies/getting-to-know-asynchronous-javascript-callbacks-promises-and-async-await-17e0673281ee


/**
 * @param {Function} fn
 * @return {Function<Promise<number>>}
 */
var promisify = function(fn) {
    return function(...args) {
        return new Promise((resolve, reject) => {
            function callback(result, error) {
                // If error, reject the Promise
                if(error) {
                    reject(error);
                // If no error, resolve the Promise
                } else {
                    resolve(result);
                }
            }

            fn(callback, ...args);
        });
    };
};

/**
 * const asyncFunc = promisify(callback => callback(42));
 * asyncFunc().then(console.log); // 42
 */
