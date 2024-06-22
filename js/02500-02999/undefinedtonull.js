
// 2775. Undefined to Null
// https://leetcode.com/problems/undefined-to-null/




/**
 * @param {Object|Array} obj
 * @return {Object|Array}
 */
var undefinedToNull = function(obj) {
    return undefinedtonull(obj);
};

// recursive function
function undefinedtonull(obj) {
    if( Array.isArray(obj) ) {
        for(let i = 0; i < obj.length; ++i)
            obj[i] = undefinedtonull(obj[i]);

    } else if( obj === null || obj === undefined ) {
        return null;

    } else if( typeof obj === 'object' ) {
        for(const [key, value] of Object.entries(obj))
            obj[key] = undefinedtonull(value);
    }

    return obj;
}

/**
 * undefinedToNull({"a": undefined, "b": 3}) // {"a": null, "b": 3}
 * undefinedToNull([undefined, undefined]) // [null, null]
 */
