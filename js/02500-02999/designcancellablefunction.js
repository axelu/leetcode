
// 2650. Design Cancellable Function
// https://leetcode.com/problems/design-cancellable-function/d




// based on other solutions

/**
 * @param {Generator} generator
 * @return {[Function, Promise]}
 */
var cancellable = function(generator) {
    let cancelFn;

    let retPromise = new Promise(function (resolve, reject) {

        cancelFn = function () {
            try {
                let res = generator.throw("Cancelled");
                resolve(res.value);
            } catch(e) {
                reject(e);
            }
        }

        function doNext(nextVal, ex) {
            let genResult;
            try {
                if( ex ) {
                    genResult = generator.throw(ex);
                } else if( nextVal === undefined ) {
                    genResult = generator.next();
                } else {
                    genResult = generator.next(nextVal);
                }
            } catch (e) {
                reject(e);
                return;
            }
            if( genResult.done ) {
                resolve(genResult.value);
                return;
            }

            let genVal = genResult.value;
            if( genVal instanceof Promise ) {
                genVal
                    .then((v) => {
                        doNext(v);
                    })
                    .catch((e) => {
                        doNext(undefined,e);
                    });
            } else {
                Promise.resolve(() => { doNext(genVal); });
            }
        }

        doNext();
    });

    return [cancelFn, retPromise];
};

/**
 * function* tasks() {
 *   const val = yield new Promise(resolve => resolve(2 + 2));
 *   yield new Promise(resolve => setTimeout(resolve, 100));
 *   return val + 1;
 * }
 * const [cancel, promise] = cancellable(tasks());
 * setTimeout(cancel, 50);
 * promise.catch(console.log); // logs "Cancelled" at t=50ms
 */
