
// 2795. Parallel Execution of Promises for Individual Results Retrieval
// https://leetcode.com/problems/parallel-execution-of-promises-for-individual-results-retrieval/




/**
 * @param {Array<Function>} functions
 * @return {Promise<Array>}
 */
var promiseAllSettled = function(functions) {

    return new Promise((resolve, reject) => {
        let l = functions.length;
        if( l === 0 )
            resolve([]);

        let mp = new Array(l);
        mp.fill(null);

        let settled = 0;
        functions.forEach(async (fn, i) => {

            try{
                let res = await fn();
                mp[i] = { status: 'fulfilled', value: res };

            } catch (err) {
               mp[i] = { status: 'rejected', reason: err };

            } finally {
                ++settled;
                if( settled === l )
                    resolve(mp);
            }
        });
    });
};


/**
 * const functions = [
 *    () => new Promise(resolve => setTimeout(() => resolve(15), 100))
 * ]
 * const time = performance.now()
 *
 * const promise = promiseAllSettled(functions);
 *
 * promise.then(res => {
 *     const out = {t: Math.floor(performance.now() - time), values: res}
 *     console.log(out) // {"t":100,"values":[{"status":"fulfilled","value":15}]}
 * })
 */
