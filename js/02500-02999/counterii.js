
// 2665. Counter II
// https://leetcode.com/problems/counter-ii/





/**
 * @param {integer} init
 * @return { increment: Function, decrement: Function, reset: Function }
 */
var createCounter = function(init) {
    const counter = {
        org: init,
        cur: init,
        increment: function() {
            ++this.cur;
            return this.cur;
        },
        decrement: function() {
            --this.cur;
            return this.cur;
        },
        reset: function() {
            this.cur = this.org;
            return this.cur;
        }
    }

    return Object.create(counter);
};

/**
 * const counter = createCounter(5)
 * counter.increment(); // 6
 * counter.reset(); // 5
 * counter.decrement(); // 4
 */
