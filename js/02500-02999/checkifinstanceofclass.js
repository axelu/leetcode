
// 2618. Check if Object Instance of Class
// https://leetcode.com/problems/check-if-object-instance-of-class/




// https://dev.to/henriquejensen/how-to-check-if-an-object-is-instance-of-a-class-javascript-3n73
// https://medium.com/javascript-scene/master-the-javascript-interview-what-s-the-difference-between-class-prototypal-inheritance-e4cd0a7562e9
// checkIfInstanceOf = function(obj, classFunction) checks if object is an instance of the given class or its superclass.
// from the 'Editorial':
// An object is considered an instance of a class if it can access the class's methods,
// or said differently, an object is an instance of a constructor function
// if it is linked to the constructor's prototype in its prototype chain
// notes:
// handle different data types
// handle cases where the instanceof keyword may not produce the expected result,
// e.g., recognize that primitives have indirect access to methods and prototypes of their appropriate constructors.
// checkIfInstance(5, Number) - the value 5 is a primitive value of type number, it is NOT an instance of the Number object
// console.log(5 instanceof Number); // Output: false
// const num = new Number(5);
// console.log(num instanceof Number); // Output: true
// BUT: in this particular problem we consider a value to be an instance of a given class
//      when the value "has access to that class's methods" and it's meant
//      that indirect access to class's methods through the boxing process described above to be also considered!!!
// see example 4 given in the problem




/**
 * @param {*} obj
 * @param {*} classFunction
 * @return {boolean}
 */
var checkIfInstanceOf = function(obj, classFunction) {

    // obj must not be null or undefined
    if( obj === null || obj === undefined )
        return false;

    // classFunction must be a function
    if( typeof classFunction !== 'function' )
        return false;

    var obj_proto = Object.getPrototypeOf(obj);
    while( obj_proto !== null ) {
        if( obj_proto === classFunction.prototype )
            return true;
        obj_proto = Object.getPrototypeOf(obj_proto);
    }

    return false;
};

/**
 * checkIfInstanceOf(new Date(), Date); // true
 */
