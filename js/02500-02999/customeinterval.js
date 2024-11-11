
// 2805. Custom Interval
// https://leetcode.com/problems/custom-interval/




/**
 * @param {Function} fn
 * @param {number} delay
 * @param {number} period
 * @return {number} id
 */

let nxtid = 0;
const running = new Map();

function customInterval(fn, delay, period){

    let func = function(funcid) {
        let count = running.get(funcid);
        if( count !== undefined ) {
            fn();
            running.set(funcid, count + 1);
            setTimeout(func, delay + period * count, funcid);
        }
    }

    running.set(nxtid, 1);
    setTimeout(func, delay, nxtid);
    return nxtid++;
}

/**
 * @param {number} id
 * @return {void}
 */
function customClearInterval(id) {
    running.delete(id);
}
