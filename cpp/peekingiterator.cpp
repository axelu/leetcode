
// 284. Peeking Iterator
// https://leetcode.com/problems/peeking-iterator/
// day 8 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/585/week-2-february-8th-february-14th/3633/



/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
private:
    queue<int> q;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	    //it = Iterator();
	}

    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        if( q.empty() ) q.push(Iterator::next());
        return q.front();
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
        if( !q.empty() ) {
            int t = q.front();
            q.pop();
            return t;
        }
	    return Iterator::next();
	}

	bool hasNext() const {
        if( !q.empty() ) return true;
	    return Iterator::hasNext();
	}
};
