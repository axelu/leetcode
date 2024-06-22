
// 2804. Array Prototype ForEach
// https://leetcode.com/problems/array-prototype-foreach/








/**
 * @param {Function} callback
 * @param {Object} context
 * @return {void}
 */
Array.prototype.forEach = function(callback, context) {

    // callback(currentValue, index, array)
    let cbck = callback.bind(context);
    for(let i = 0; i < this.length; ++i) {
        cbck(this[i], i, this);
    }

}

/**
 *  const arr = [1,2,3];
 *  const callback = (val, i, arr) => arr[i] = val * 2;
 *  const context = {"context":true};
 *
 *  arr.forEach(callback, context) 
 *
 *  console.log(arr) // [2,4,6]
 */
