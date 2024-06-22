
// 2755. Deep Merge of Two Objects
// https://leetcode.com/problems/deep-merge-of-two-objects/



/**
 * @param {null|boolean|number|string|Array|Object} obj1
 * @param {null|boolean|number|string|Array|Object} obj2
 * @return {null|boolean|number|string|Array|Object}
 */
var deepMerge = function(obj1, obj2) {
    return merge(obj1, obj2);
};

// recursive function
function merge(obj1, obj2) {
    if( Array.isArray(obj1) && Array.isArray(obj2) ) {
        let obj1_n = obj1.length;
        let obj2_n = obj2.length;
        let arr = new Array();
        for(let i = 0; i < Math.max(obj1_n, obj2_n); ++i) {
            if( i < obj1_n && i < obj2_n )
                arr.push(merge(obj1[i], obj2[i]));
            else if( i < obj1_n )
                arr.push(obj1[i]);
            else // i < obj2_n
                arr.push(obj2[i]);
        }
        return arr;

    } else if( !Array.isArray(obj1) && !Array.isArray(obj2) &&
               typeof obj1 === 'object' && obj1 !== null && typeof obj2 === 'object' && obj2 !== null ) {

        let entries = new Map();

        let mp2 = new Map(); // keyed by keys in obj2
        for(const [key, value] of Object.entries(obj2))
            mp2.set(key, value);

        for(const [key, value] of Object.entries(obj1)) {
            let entry = mp2.get(key);
            if( entry !== undefined ) {
                entries.set(key, merge(value, entry));
                mp2.delete(key);
            } else {
                entries.set(key, value);
            }
        }
        const it = mp2.entries();
        let p = it.next().value;
        while( p ) {
            entries.set(p[0], p[1]);
            p = it.next().value;
        }

        return Object.fromEntries(entries);
    }

    return obj2;
}

/**
 * let obj1 = {"a": 1, "c": 3}, obj2 = {"a": 2, "b": 2};
 * deepMerge(obj1, obj2); // {"a": 2, "c": 3, "b": 2}
 */
