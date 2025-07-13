
// 2691 Immutability Helper
// https://leetcode.com/problems/immutability-helper/


// credits to https://leetcode.com/problems/immutability-helper/solutions/4177563/the-original-object-must-be-copied-but-only-shallowly

var ImmutableHelper = function(obj) {
    this.originalObj = obj;
    this.mutated = false;

    // see 2692. Make Object Immutable https://leetcode.com/problems/make-object-immutable/
    this.makeImmutable = function(obj, mutatedObj) {

        // 'set' trap throws an error when an attempt is made to modify a property.
        const setTrap = function(target, prop, value) {
            // throw Array.isArray(target) ? `Error Modifying Index: ${prop}` : `Error Modifying: ${prop}`;
            if( target[prop] !== value ) {
                mutatedObj[prop] = value;
                this.mutated = true;
            }
        }

        // 'get' trap creates a new proxy for nested objects or functions,
        // while returning primitive values and 'prototype' property as is.
        const getTrap = function(target, prop) {
            if( target[prop] !== null && typeof target[prop] === 'object' ) {
                if (mutatedObj[prop] === undefined) {
                    mutatedObj[prop] = {};
                }
                return this.makeImmutable(target[prop], mutatedObj[prop]);
            }
            // if at this point we didn't define the requested property on our
            // mutated object, then we need to return the property from our original
            return mutatedObj[prop] === undefined ? Reflect.get(target, prop) : mutatedObj[prop];
        }

        const handler = {set: setTrap.bind(this), get: getTrap.bind(this)};
        return new Proxy(obj, handler);
    };

    this.shallowCopy = function(obj, mutatedObj) {
        if( obj === null || typeof obj !== 'object' || typeof mutatedObj !== 'object' )
		    return mutatedObj;

        let ret;
        if( Array.isArray(obj) ) {
            ret = [...obj];
            for(let [k, v] of Object.entries(mutatedObj)) {
                const idx = parseInt(k, 10);
                ret[idx] = this.shallowCopy(obj[idx], v);
            }

        } else {
            ret = {...obj};
            for(let [k, v] of Object.entries(mutatedObj)) {
                ret[k] = this.shallowCopy(obj[k], v);
            }
        }
        return ret;
    }

};

/**
 * @param {Function} mutator
 * @return {JSON} clone of obj
 */
ImmutableHelper.prototype.produce = function(mutator) {
    // correct result but TLE on a deeply neested object test case 24/26 as of 3/22/2025
    // let o_new = JSON.parse(JSON.stringify(this.o)); // deep copy clone
    // mutator(o_new);
    // return o_new;

    // the mutant object will have only the changed properties
    const mutant = {};
    var proxy = this.makeImmutable(this.originalObj, mutant);
    mutator(proxy);

    if( this.mutated ) {
        // we create a shallow copy, meaning we only expand on the keys
        // that led to the mutations.
        // All other objects/arrays will be a shallow copy of the original.
        let ret = this.shallowCopy(this.originalObj, mutant);

        // reset
        this.mutated = false;

        return ret;
    }

    // mutator didn't change anything, return original object
    return this.originalObj;
};

/**
 * const originalObj = {"x": 5};
 * const mutator = new ImmutableHelper(originalObj);
 * const newObj = mutator.produce((proxy) => {
 *   proxy.x = proxy.x + 1;
 * });
 * console.log(originalObj); // {"x: 5"}
 * console.log(newObj); // {"x": 6}
 */
