
// 2694. Event Emitter
// https://leetcode.com/problems/event-emitter/



class EventEmitter {

    #subscriptions;

    constructor() {
        this.#subscriptions = new Map();
    }

    /**
     * @param {string} eventName
     * @param {Function} callback
     * @return {Object}
     */
    subscribe(eventName, callback) {

        let subscription = this.#subscriptions.get(eventName);
        if( subscription === undefined ) {
            let subscribers = new Set();
            subscribers.add(callback);
            this.#subscriptions.set(eventName, subscribers);
        } else {
            subscription.add(callback);
        }

        return {
            unsubscribe: () => {
                this.unsubscribe(eventName, callback);
            }
        };
    }

    /**
     * @param {string} eventName
     * @param {Array} args
     * @return {Array}
     */
    emit(eventName, args = []) {

        let subscription = this.#subscriptions.get(eventName);
        if( subscription === undefined )
            return [];

        let ret = new Array();
        const it = subscription.keys();
        let fn = it.next().value;
        while( fn ) {
            ret.push(fn(...args));
            fn = it.next().value;
        }

        return ret;
    }

    unsubscribe(eventName, key) {
        let subscription = this.#subscriptions.get(eventName);
        if( subscription !== undefined ) {
            subscription.delete(key);
            if( subscription.size === 0 ) {
                this.#subscriptions.delete(eventName);
            }
        }
        return undefined;
    }
}

/**
 * const emitter = new EventEmitter();
 *
 * // Subscribe to the onClick event with onClickCallback
 * function onClickCallback() { return 99 }
 * const sub = emitter.subscribe('onClick', onClickCallback);
 *
 * emitter.emit('onClick'); // [99]
 * sub.unsubscribe(); // undefined
 * emitter.emit('onClick'); // []
 */
