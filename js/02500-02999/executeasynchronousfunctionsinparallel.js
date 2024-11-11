
// 2721. Execute Asynchronous Functions in Parallel
// https://leetcode.com/problems/execute-asynchronous-functions-in-parallel/

// see also
// 2636. Promise Pool
// https://leetcode.com/problems/promise-pool/




/**
 * @param {Array<Function>} functions
 * @return {Promise<any>}
 */
var promiseAll = function(functions) {

    return new Promise((resolve, reject) => {

        let l = functions.length;
        let dop = 0; // degree of parallelism
        let i = 0;
        const result = new Array(l);
        let rec = function() {
            if( i === l ) {
                if( dop === 0 )
                    resolve(result);
                else
                    return;
            }

            while( dop < l && i < l ) {
                ++dop;
                let promise = functions[i]();
                let idx = i;
                promise.then(
                    (value) => {
                        result[idx] = value;
                        --dop;
                        rec();
                    },
                    (reason) => {
                        reject(reason);
                    }
                );
                ++i;
            }
        }
        rec();
    });
};

/**
 * const promise = promiseAll([() => new Promise(res => res(42))])
 * promise.then(console.log); // [42]
 */
