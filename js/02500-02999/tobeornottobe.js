
// 2704. To Be Or Not To Be
// https://leetcode.com/problems/to-be-or-not-to-be/






/**
 * @param {string} val
 * @return {Object}
 */
var expect = function(val) {

    let obj = new Object();

    obj.value = val;

    obj.toBe = function(a) {
        if( this.value === a )
            return true;
        else
            throw new Error("Not Equal");
    };

    obj.notToBe = function(a) {
        if( this.value !== a )
            return true;
        else
            throw new Error("Equal");
    }


    return obj;
};

/**
 * expect(5).toBe(5); // true
 * expect(5).notToBe(5); // throws "Equal"
 */
