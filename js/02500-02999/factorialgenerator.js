
// 2803. Factorial Generator
// https://leetcode.com/problems/factorial-generator/




/**
 * @param {number} n
 * @yields {number}
 */
function* factorial(n) {
    let limit = n;
    let f = 0;
    let ret = 1;

    do{
        ++f;
        ret = f * ret;
        yield ret;
    } while ( f < limit );
};

/**
 * const gen = factorial(2);
 * gen.next().value; // 1
 * gen.next().value; // 2
 */
