
// 2705. Compact Object
// https://leetcode.com/problems/compact-object/






/**
 * @param {Object|Array} obj
 * @return {Object|Array}
 */
var compactObject = function(obj) {
    return remove_falsy(obj);
};

// recursive function
function remove_falsy(obj) {
    let ret;
    if( Array.isArray(obj) ) {
        ret = new Array();
        for(let i = 0; i < obj.length; ++i) {
            if( !Boolean(obj[i]) )
                continue;

            ret.push(remove_falsy(obj[i]));
        }

    } else if( typeof obj === 'object' ) {
        let entries = new Map();
        for(const [key, value] of Object.entries(obj)) {
            if( !Boolean(value) )
                continue;

            entries.set(key, remove_falsy(value));
        }
        ret = Object.fromEntries(entries);

    } else {
        ret = obj; // not an Array and not an Object and Boolean(obj) == true
    }

    return ret;
}
