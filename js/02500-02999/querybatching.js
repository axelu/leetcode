
// 2756. Query Batching
// https://leetcode.com/problems/query-batching/





// based on editorial solution

/**
 * @param {Function} queryMultiple
 * @param {number} t
 * @return {void}
 */
var QueryBatcher = function(queryMultiple, t) {
    this.queryMultiple = queryMultiple;
    this.t = t;
    this.isAvailable = true;  // Flag to indicate if the batcher can immediately process a query
    this.stashed = [];  // Temporary storage for queries arriving during a throttle time
};

/**
 * @param {string} key
 * @return {Promise<string>}
 */
QueryBatcher.prototype.getValue = function(key) {
    return new Promise((resolve) => {
        if (this.isAvailable) {
            this.isAvailable = false;
            // execute the queryMultiple wit the one key given and assing result to resolve
            this.queryMultiple([key]).then(results => resolve(results[0]));
            this.cooldown();  // Start the throttle time
            return;
        }
        // If the batcher is not available, stash the query for later processing
        this.stashed.push({ key, resolve });
        // note that we are putting an object literal into our stash
        // in our case the property keys are 'key' and 'resolve'
        // stash will look like this for example:
        // [ { key: 'b', resolve: [Function (anonymous)] },
        //   { key: 'c', resolve: [Function (anonymous)] } ]
  });
};

QueryBatcher.prototype.cooldown = function() {
    setTimeout(() => {
        // If no stashed queries exist after the throttle time, set the batcher as available
        if (this.stashed.length === 0) {
            this.isAvailable = true;
            return;
        }

        // Prepare the stashed keys for batching and keep the resolve functions for later
        const keysToQuery = this.stashed.map(item => item.key);
        const resolvers = this.stashed.map(item => item.resolve);

        // Clear the stashed queries as they are about to be processed
        this.stashed = [];

        // Process the batched queries and return results to the respective callers
        this.queryMultiple(keysToQuery)
            .then(results => {
                resolvers.forEach((resolve, idx) => {
                    resolve(results[idx]);
                });
            });

        // Start another cooldown for the next batch
        this.cooldown();
    }, this.t);
};

/**
 * async function queryMultiple(keys) {
 *   return keys.map(key => key + '!');
 * }
 *
 * const batcher = new QueryBatcher(queryMultiple, 100);
 * batcher.getValue('a').then(console.log); // resolves "a!" at t=0ms
 * batcher.getValue('b').then(console.log); // resolves "b!" at t=100ms
 * batcher.getValue('c').then(console.log); // resolves "c!" at t=100ms
 */
