
// 2622. Cache With Time Limit
// https://leetcode.com/problems/cache-with-time-limit/






var TimeLimitedCache = function() {

};

TimeLimitedCache.prototype.map = new Map();

TimeLimitedCache.prototype.evict = function(key, map) {
    map.delete(key);
};

/**
 * @param {number} key
 * @param {number} value
 * @param {number} duration time until expiration in ms
 * @return {boolean} if un-expired key already existed
 */
TimeLimitedCache.prototype.set = function(key, value, duration) {
    let entry = this.map.get(key);
    if( entry === undefined ) {
        let timeoutID = setTimeout(this.evict, duration, key, this.map);
        this.map.set(key, {val: value, timeoutID: timeoutID});
        return false;
    } else {
        clearTimeout(entry.timeoutID);
        let timeoutID = setTimeout(this.evict, duration, key, this.map);
        this.map.set(key, {val: value, timeoutID: timeoutID});
        return true;
    }
};

/**
 * @param {number} key
 * @return {number} value associated with key
 */
TimeLimitedCache.prototype.get = function(key) {
    let entry = this.map.get(key);
    return entry !== undefined ? entry.val : -1;
};

/**
 * @return {number} count of non-expired keys
 */
TimeLimitedCache.prototype.count = function() {
    return this.map.size;
};

/**
 * const timeLimitedCache = new TimeLimitedCache()
 * timeLimitedCache.set(1, 42, 1000); // false
 * timeLimitedCache.get(1) // 42
 * timeLimitedCache.count() // 1
 */
