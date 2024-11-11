
// 2759. Convert JSON String to Object
// https://leetcode.com/problems/convert-json-string-to-object/





/**
 * @param {string} str
 * @return {null|boolean|number|string|Array|Object}
 */
var jsonParse = function(str) {
    // str is valid JSON string
    // includes strings, numbers, arrays, objects, booleans, and null
    // will not include invisible characters (includes space) and escape characters

    let pos = 0;

    let get_obj = function() {
        const entries = new Map();
        ++pos;
        while( str[pos] !== '}' ) {
            if( str[pos] === ',' )
                ++pos;

            // key:value
            const key = get_primitive();
            ++pos; // :
            if( str[pos] === '{' ) {
                const value = get_obj();
                entries.set(key,value);
            } else if( str[pos] === '[' ) {
                const value = get_arr();
                entries.set(key,value);
            } else {
                const value = get_primitive();
                entries.set(key,value);
            }
        }
        ++pos;
        return Object.fromEntries(entries);
    }

    let get_arr = function() {
        const arr = new Array();
        ++pos;
        while( str[pos] !== ']' ) {
            if( str[pos] === ',' ) {
                ++pos;
            } else if( str[pos] === '{' ) {
                arr.push(get_obj());
            } else if( str[pos] === '[' ) {
                arr.push(get_arr());
            } else {
                arr.push(get_primitive());
            }
        }
        ++pos;
        return arr;
    }

    let get_primitive = function() {
        // assume string enclosed in ""
        if( str[pos] === '"' ) {        // string
            ++pos;
            const s = pos;
            while( str[pos] !== '"' )
                ++pos;

            const ret = str.substring(s, pos);
            ++pos;
            return ret;

        } else if( str[pos] === 'f' ) { // false
            pos += 5;
            return false;

        } else if( str[pos] === 't' ) { // true
            pos += 4;
            return true;

        } else if( str[pos] === 'n' ) { // null
            pos += 4;
            return null;

        } else {                        // number
            const s = pos;
            while( str[pos] !== ']' && str[pos] !== '}' && str[pos] !== ','  && pos < str.length )
                ++pos;

            const ret = new Number(str.substring(s, pos));
            return ret;
        }
    }

    if( str[0] === '{' ) {
        return get_obj();
    } else if( str[0] === '[' ) {
        return get_arr();
    } else {
        return get_primitive();
    }
};
