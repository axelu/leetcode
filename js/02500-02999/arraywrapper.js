
// 2695. Array Wrapper
// https://leetcode.com/problems/array-wrapper/




/**
 * @param {number[]} nums
 */
var ArrayWrapper = function(nums) {
    this.arr = nums;
};

ArrayWrapper.prototype.valueOf = function() {
    let ret = 0;
    for(let i = 0; i < this.arr.length; ++i)
        ret += this.arr[i];
    return ret;
}

ArrayWrapper.prototype.toString = function() {
    let ret = "[";
    for(let i = 0; i < this.arr.length; ++i) {
        if( i > 0 )
            ret += ",";
        ret += this.arr[i];
    }
    ret += "]";
    return ret;
}

/**
 * const obj1 = new ArrayWrapper([1,2]);
 * const obj2 = new ArrayWrapper([3,4]);
 * obj1 + obj2; // 10
 * String(obj1); // "[1,2]"
 * String(obj2); // "[3,4]"
 */
