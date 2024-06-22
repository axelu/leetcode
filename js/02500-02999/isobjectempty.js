
// 2727. Is Object Empty
// https://leetcode.com/problems/is-object-empty/



/**
 * @param {Object|Array} obj
 * @return {boolean}
 */
var isEmpty = function(obj) {
    if( Array.isArray(obj) ) {
        return obj.length == 0;

    } else {
        return Object.keys(obj).length == 0;

    }
};
