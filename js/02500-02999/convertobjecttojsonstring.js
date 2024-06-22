
// 2633. Convert Object to JSON String
// https://leetcode.com/problems/convert-object-to-json-string/





/**
 * @param {null|boolean|number|string|Array|Object} object
 * @return {string}
 */
var jsonStringify = function(object) {
    // value can be a string, number, array, object, boolean, or null
    // solve it without using the built-in JSON.stringify method

    return stringify(object);
};

// recursive function
function stringify(obj) {
    if( Array.isArray(obj) ) {
        let s = "[";
        for(let i = 0; i < obj.length; ++i) {
            if( i > 0 )
                s = s.concat(",");
            s = s.concat(stringify(obj[i]));
        }
        s = s.concat("]");
        return s;

    } else if( obj === null ) {
        return "null";

    } else if( typeof obj === 'object' ) { // we know it is not null
        let s = "{";
        for(const [key, value] of Object.entries(obj)) {
            if( s !== "{" )
                s = s.concat(",");
            s = s.concat("\"",key,"\":",stringify(value));
        }
        s = s.concat("}");
        return s;

    } else if( typeof obj === 'string' ) {
        let s = "\"";
        s = s.concat(obj,"\"");
        return s;

    } else { // number or boolean
        return obj.toString();

    }
}
