
// 2675. Array of Objects to Matrix
// https://leetcode.com/problems/array-of-objects-to-matrix/




/**
 * @param {Array} arr
 * @return {(string | number | boolean | null)[][]}
 */
var jsonToMatrix = function(arr) {
    // arr is an array of objects or arrays

    const mp = new Map();
    let arr_idx = 0;

    let level = function() {
        const it = mp.values();
        let val = it.next().value;
        while( val ) {
            while( val.length <= arr_idx )
                val.push("");
            val = it.next().value;
        }
    }

    let add = function(key, value) {
        let f = mp.get(key);
        if( f === undefined ) {
            // we found a new key
            const a = new Array();
            for(let i = 0; i < arr_idx; ++i)
                a.push("");
            a.push(value);
            mp.set(key, a);

        } else {
            while( f.length < arr_idx )
                f.push("");
            f.push(value);
        }
    }

    let process_obj = function(prefix, obj) {
        for(const [key, value] of Object.entries(obj)) {
            let k = prefix === "" ? key : prefix.concat('.', key);

            if( Array.isArray(value) ) {
                process_arr(k, value);

            } else if( typeof value === 'object' ) {
                if( value === null )
                    add(k, null);
                else
                    process_obj(k, value);
            } else {
                add(k, value);
            }
        }
    }

    let process_arr = function(prefix, a) {
        for(let i = 0; i < a.length; ++i) {
            let k = prefix === "" ? i.toString() : prefix.concat('.', i.toString());

            if( Array.isArray(a[i]) ) {
                process_arr(k, a[i]);

            } else if( typeof a[i] === 'object' ) {
                if( a[i] === null )
                    add(k, null);
                else
                    process_obj(k, a[i]);
            } else {
                add(k, a[i]);
            }
        }
    }

    for(; arr_idx < arr.length; ++arr_idx) {
        if( Array.isArray(arr[arr_idx]) ) {
            process_arr("", arr[arr_idx]);
            level();
        } else {
            process_obj("", arr[arr_idx]);
            level();
        }
    }
    // console.log(mp);

    // sort
    const mpsorted = new Map([...mp.entries()].sort());
    // console.log(mpsorted);

    // transform map into end result
    // rows: we have arr.length + 1 rows, with 1st row being keys
    // cols: number of keys in our map
    const ans = new Array();
    for(let i = 0; i < arr.length + 1; ++i) {
        const row = new Array(mp.size);
        ans.push(row);
    }
    let j = 0;
    const it = mpsorted.entries();
    let p = it.next().value;
    while( p ) {
        let key = p[0];
        let a = p[1];

        ans[0][j] = key;
        for(let i = 0; i < a.length; ++i)
            ans[i+1][j] = a[i];

        p = it.next().value;
        ++j;
    }

    return ans;
};
