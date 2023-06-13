
// 2690. Infinite Method Object
// https://leetcode.com/problems/infinite-method-object/



/**
 * @return {Object}
 */
var createInfiniteObject = function() {
    return new Proxy(
        {},
        {
            get(target, prop, receiver) {
                return () => {
                    return prop;
                };
            },
        },
    );
};

/**
 * const obj = createInfiniteObject();
 * obj['abc123'](); // "abc123"
 */
