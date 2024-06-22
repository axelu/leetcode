
// 2794. Create Object from Two Arrays
// https://leetcode.com/problems/create-object-from-two-arrays/





/**
 * @param {Array} keysArr
 * @param {Array} valuesArr
 * @return {Object}
 */
var createObject = function(keysArr, valuesArr) {
    // keysArr.length === valuesArr.length

    let entries = new Map();
    for(let i = 0; i < keysArr.length; ++i) {
        let key;
        if( keysArr[i] == null )
            key = "null";
        else
            key = keysArr[i].toString();

        if( entries.has(key) )
            continue;
        entries.set(key, valuesArr[i]);
    }

    return Object.fromEntries(entries);
};
