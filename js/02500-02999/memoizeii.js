
// 2630. Memoize II
// https://leetcode.com/problems/memoize-ii/






/**
 * @param {Function} fn
 * @return {Function}
 */
function memoize(fn) {

    let root = {children: new Map(), endofarguments: false, result: undefined}; // Trie

    let searchadd = function(args) {
        let tn = root;
        for(let i = 0; i < args.length; ++i) {
            let key = args[i];
            if( !tn.children.has(key) ) {
                let child = {children: new Map(), endofarguments: false, result: undefined};
                tn.children.set(key, child);
            }
            tn = tn.children.get(key);
        }
        return tn;
    }

    return function() {
        let ret;
        let seen = searchadd(arguments);
        if( !seen.endofarguments ) {
            ret = fn(...arguments);
            seen.endofarguments = true;
            seen.result = ret;
        } else {
            ret = seen.result;
        }
        return ret;
    }
}


/**
 * let callCount = 0;
 * const memoizedFn = memoize(function (a, b) {
 *	 callCount += 1;
 *   return a + b;
 * })
 * memoizedFn(2, 3) // 5
 * memoizedFn(2, 3) // 5
 * console.log(callCount) // 1
 */
