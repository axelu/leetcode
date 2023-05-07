
// 2648. Generate Fibonacci Sequence
// https://leetcode.com/problems/generate-fibonacci-sequence/



/**
 * @return {Generator<number>}
 */
var fibGenerator = function*() {
    yield 0;
    yield 1;

    let a = 0;
    let b = 1;

    while (true) {
        let ret = a + b;

        a = b;
        b = ret;

        yield ret;
    }
};

/**
 * const gen = fibGenerator();
 * gen.next().value; // 0
 * gen.next().value; // 1
 */
