
// 2637. Promise Time Limit
// https://leetcode.com/problems/promise-time-limit/



/**
 * @param {Function} fn
 * @param {number} t
 * @return {Function}
 */
var timeLimit = function(fn, t) {
	return async function(...args) {
        let fr = fn(...args);
        let to = new Promise((resolve, reject) => {
		    setTimeout(() => {
                reject("Time Limit Exceeded");
		    }, t);
	    });

        return Promise.race([fr, to]);
    }
};

/**
 * const limited = timeLimit((t) => new Promise(res => setTimeout(res, t)), 100);
 * limited(150).catch(console.log) // "Time Limit Exceeded" at t=100ms
 */
