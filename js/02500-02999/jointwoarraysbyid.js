
// 2722. Join Two Arrays by ID
// https://leetcode.com/problems/join-two-arrays-by-id/






/**
 * @param {Array} arr1
 * @param {Array} arr2
 * @return {Array}
 */
var join = function(arr1, arr2) {
    // it is guaranteed that the object id's in each array byitself are unique

    let joined = new Map();
    for(let i = 0; i < arr1.length; ++i) {
        let key = arr1[i].id;
        joined.set(key, arr1[i]);
    }
    for(let i = 0; i < arr2.length; ++i) {
        let key = arr2[i].id;
        let entry = joined.get(key);
        if( entry === undefined ) {
            joined.set(key, arr2[i]);
        } else {
            joined.set(key, Object.assign(entry, arr2[i])); // merge objects
        }
    }

    let ret = new Array();
    const it = joined.values();
    let obj = it.next().value;
    while( obj ) {
        ret.push(obj);
        obj = it.next().value;
    }
    // ret.sort(cmp);
    ret.sort((a, b) => a.id < b.id ? -1 : 1); // it is guaranteed that a.id != b.id
    return ret;
};

function cmp(a, b) {
    // A negative value indicates that a should come before b.
    // A positive value indicates that a should come after b.
    // Zero or NaN indicates that a and b are considered equal.

    // it is guaranteed that a.id != b.id

    return a.id < b.id ? -1 : 1
}
