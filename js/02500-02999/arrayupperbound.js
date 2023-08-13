
// 2774. Array Upper Bound
// https://leetcode.com/problems/array-upper-bound/





/**
 * @param {number} target
 * @return {number}
 */
Array.prototype.upperBound = function(target) {
    let ret = -1;
    let s = 0;
    let e = this.length-1;
    let mid;
    while(s <= e) {
        mid = s + Math.floor((e-s)/2);
        if( this[mid] == target ) {
            ret = mid;
        }
        if( this[mid] <= target ) {
            s = mid + 1;
        } else {
            e = mid - 1;
        }
    }

    return ret;
};


// [3,4,5].upperBound(5); // 2
// [1,4,5].upperBound(2); // -1
// [3,4,6,6,6,6,7].upperBound(6) // 5
