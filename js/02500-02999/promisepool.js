
// 2636. Promise Pool
// https://leetcode.com/problems/promise-pool/

// see also https://agostonfung.medium.com/simple-javascript-promise-pool-c851aa50edbf



/**
 * @param {Function[]} functions
 * @param {number} n
 * @return {Promise<any>}
 */
var promisePool = async function(functions, n) {

    return new Promise((resolve) => {

        let l = functions.length;
        let dop = 0; // degree of parallelism
        let i = 0;

        let rec = function() {
            if( i === l ) {
                if( dop === 0 )
                    resolve();
                else
                    return;
            }

            while( dop < n && i < l ) {
                ++dop;
                let promise = functions[i++]();
                promise.then(() => {
                    --dop;
                    rec();
                });
            }
        }
        rec();
    });
};

/**
 * const sleep = (t) => new Promise(res => setTimeout(res, t));
 * promisePool([() => sleep(500), () => sleep(400)], 1)
 *   .then(console.log) // After 900ms
 */
