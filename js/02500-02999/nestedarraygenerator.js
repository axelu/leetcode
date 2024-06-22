
// 2649. Nested Array Generator
// https://leetcode.com/problems/nested-array-generator/





/**
 * @param {Array} arr
 * @return {Generator}
 */
var inorderTraversal = function*(arr) {
    /*
    let a = arr.flat(Infinity);
    for(let i = 0; i < a.length; ++i) {
        yield a[i];
    }
    */

    // solve this without creating a new flattened version of the array

    let stck = new Array(); // arr, next pos
    if( arr.length > 0 )
        stck.push([arr, 0]);

    while( stck.length > 0 ) {
        let [a, i] = stck[stck.length - 1];
        stck.pop();

        if( !Array.isArray(a[i]) )
            yield a[i];

        if( i + 1 < a.length )
            stck.push([a, i + 1]);

        if( Array.isArray(a[i]) && a[i].length > 0 )
            stck.push([a[i], 0]);
    }
};

/**
 * const gen = inorderTraversal([1, [2, 3]]);
 * gen.next().value; // 1
 * gen.next().value; // 2
 * gen.next().value; // 3
 */
