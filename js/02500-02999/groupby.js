
// 2631. Group By
// https://leetcode.com/problems/group-by/





/**
 * @param {Function} fn
 * @return {Object}
 */
Array.prototype.groupBy = function(fn) {

    let entries = new Map();
    for(let i = 0; i < this.length; ++i) {
        let key = fn(this[i]);
        let entry = entries.get(key);
        if( entry === undefined ) {
            entries.set(key, [this[i]]);
        } else {
            entry.push(this[i]);
        }
    }

    return Object.fromEntries(entries);
};

/**
 * [1,2,3].groupBy(String) // {"1":[1],"2":[2],"3":[3]}
 */
