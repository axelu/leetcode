
// 2821. Delay the Resolution of Each Promise
// https://leetcode.com/problems/delay-the-resolution-of-each-promise/





/**
 * @param {Array<Function>} functions
 * @param {number} ms
 * @return {Array<Function>}
 */
var delayAll = function(functions, ms) {

    const arr = new Array();
    for(let i = 0; i < functions.length; ++i) {
        /*
        let fn = function() {
            return new Promise(resolve => setTimeout(resolve, ms));
        }
        */

        let fn = function() {



            return new Promise((resolve, reject) => {
                let promise = functions[i]();
                promise.then(
                    (value) => {
                        // resolve(value);
                        setTimeout(resolve, ms);
                    },
                    (reason) => {
                        // reject(reason);
                        setTimeout(reject, ms);
                    }
                );




           // setTimeout(functions[i].apply(), ms)



        });
        };


        arr.push(fn);
    }
    return arr;
};


