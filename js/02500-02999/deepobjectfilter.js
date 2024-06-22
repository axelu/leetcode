
// 2823. Deep Object Filter
// https://leetcode.com/problems/deep-object-filter/





/**
 * @param {Object|Array} obj
 * @param {Function} fn
 * @return {Object|Array|undefined}
 */
var deepFilter = function(obj, fn) {
    return filter(obj, fn);
};

// recursive function
function filter(obj, fn) {
    if( Array.isArray(obj) ) {
        let ret = new Array();
        for(let i = 0; i < obj.length; ++i) {
            let t = filter(obj[i], fn);
            if( t !== undefined )
                ret.push(t);
        }
        return ret.length === 0 ? undefined : ret;

    } else if( typeof obj === 'object' && obj !== null ) {
        let entries = new Map();
        for(const [key, value] of Object.entries(obj)) {
            let t = filter(value, fn);
            if( t !== undefined )
                entries.set(key, t);
        }
        return entries.size === 0 ? undefined : Object.fromEntries(entries);
    }

    return fn(obj) === false ? undefined : obj;
}
