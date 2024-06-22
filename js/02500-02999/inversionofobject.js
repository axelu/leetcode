
// 2822. Inversion of Object
// https://leetcode.com/problems/inversion-of-object/






/**
 * @param {Object|Array} obj
 * @return {Object}
 */
var invertObject = function(obj) {
    // It is guaranteed that the values in obj are only strings.

    let entries = new Map();

    if( Array.isArray(obj) ) {
        for(let i = 0; i < obj.length; ++i) {
            let key = obj[i];
            if( entries.has(key) ) {
                if( Array.isArray(entries.get(key)) ) {
                    entries.get(key).push(i.toString())
                } else {
                    let t = entries.get(key);
                    entries.set(key, [t, i.toString()]);
                }
            } else {
                entries.set(key, i.toString());
            }
        }

    } else {
        // normally
        // for(const [key, value] of Object.entries(obj)) {
        // but because the ask is to create intersion of object, we will swap key and value
        for(const [value, key] of Object.entries(obj)) {
            if( entries.has(key) ) {
                if( Array.isArray(entries.get(key)) ) {
                    entries.get(key).push(value)
                } else {
                    let t = entries.get(key);
                    entries.set(key, [t, value]);
                }
            } else {
                entries.set(key, value);
            }
        }
    }

    return Object.fromEntries(entries);
};
