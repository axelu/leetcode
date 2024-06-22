
// 2797. Partial Function with Placeholders
// https://leetcode.com/problems/partial-function-with-placeholders/





/**
 * @param {Function} fn
 * @param {Array} args
 * @return {Function}
 */
var partial = function(fn, args) {

    return function(...restArgs) {

        let arr = [];
        let j = 0; // index restArgs
        for(let i = 0; i < args.length; ++i) {
            if( args[i] == "_" ) {
                arr.push(restArgs[j]);
                ++j;
            } else {
                arr.push(args[i]);
            }
        }
        for(; j < restArgs.length; ++j)
            arr.push(restArgs[j]);

        return fn(...arr);
    }
};
