
// 2700. Differences Between Two Objects
// https://leetcode.com/problems/differences-between-two-objects/






/**
 * @param {Object|Array} obj1
 * @param {Object|Array} obj2
 * @return {Object|Array}
 */
function objDiff(obj1, obj2) {
    let ret = diff(obj1, obj2);
    return ret !== null ? ret : {};
};

// recursive function
function diff(obj1, obj2) {
    // if different type we are done -> return 'difference array'
    // if same type, start comparying 'keys'

    if( typeof obj1 !== typeof obj2 ) {
        return [obj1, obj2];

    } else { // typeof obj1 === typeof obj2
        if( Array.isArray(obj1) && Array.isArray(obj2) ) {
            let i_limit = Math.min(obj1.length, obj2.length);
            let entries = new Map();
            for(let i = 0; i < i_limit; ++i) {
                let t = diff(obj1[i], obj2[i]);
                if( t !== null )
                    entries.set(i, t);
            }
            return entries.size === 0 ? null : Object.fromEntries(entries);

        } else if( Array.isArray(obj1) ) { // typeof obj2 === 'object' OR null
            return [obj1, obj2];

        } else if( Array.isArray(obj2) ) { // typeof obj1 === 'object' OR null
            return [obj1, obj2];

        } else if( typeof obj1 === 'object' ) {
            if( (obj1 === null && obj2 !== null) || (obj1 !== null && obj2 === null) ) {
                return [obj1, obj2];

            } else if( obj1 !== null && obj2 !== null ) {
                let entries = new Map();
                let mp1 = new Map(); // keys in obj1
                for(const [key, value] of Object.entries(obj1)) {
                    mp1.set(key, value);
                }
                for(const [key, value] of Object.entries(obj2)) {
                    let entry = mp1.get(key);
                    if( entry !== undefined ) {
                        let t = diff(entry, value);
                        if( t !== null )
                            entries.set(key, t);
                    }
                }
                return entries.size === 0 ? null : Object.fromEntries(entries);
            }

        } else {
            if( obj1 !== obj2 ) // type already compared
                return  [obj1, obj2];
        }
    }

    return null;
}
