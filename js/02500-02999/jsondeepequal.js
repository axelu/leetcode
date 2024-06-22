
// 2628. JSON Deep Equal
// https://leetcode.com/problems/json-deep-equal/







/**
 * @param {null|boolean|number|string|Array|Object} o1
 * @param {null|boolean|number|string|Array|Object} o2
 * @return {boolean}
 */
var areDeeplyEqual = function(o1, o2) {
    return diff(o1, o2);
};

// recursive function
function diff(obj1, obj2) {
    // if different type we are done -> return false
    // if same type, start comparying 'keys'

    if( typeof obj1 !== typeof obj2 ) {
        return false;

    } else { // typeof obj1 === typeof obj2
        if( Array.isArray(obj1) && Array.isArray(obj2) ) {
            let obj1_n = obj1.length;
            let obj2_n = obj2.length;
            if( obj1_n !== obj2_n )
                return false;

            for(let i = 0; i < obj1_n; ++i) {
                if( !diff(obj1[i], obj2[i]) )
                    return false;;
            }

        } else if( Array.isArray(obj1) ) { // typeof obj2 === 'object' OR null
            return false;

        } else if( Array.isArray(obj2) ) { // typeof obj1 === 'object' OR null
            return false;

        } else if( typeof obj1 === 'object' ) {
            if( (obj1 === null && obj2 !== null) || (obj1 !== null && obj2 === null) ) {
                return false;

            } else if( obj1 !== null && obj2 !== null ) {
                let mp1 = new Map(); // keys in obj1
                for(const [key, value] of Object.entries(obj1)) {
                    mp1.set(key, value);
                }
                let mp2 = new Map(); // keys in obj2
                for(const [key, value] of Object.entries(obj2)) {
                    mp2.set(key, value);
                }
                if( mp1.size !== mp2.size )
                    return false;

                const it = mp1.entries();
                let p = it.next().value;
                while( p ) {
                    let key = p[0];
                    let o1 = p[1];
                    let o2 = mp2.get(key);
                    if( o2 === undefined || !diff(o1, o2) )
                        return false;
                    p = it.next().value;
                }
            }

        } else {
            if( obj1 !== obj2 ) // type already compared
                return  false;
        }
    }

    return true;
}
