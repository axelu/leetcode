
// 379. Design Phone Directory
// https://leetcode.com/problems/design-phone-directory/





class PhoneDirectory {
private:
    stack<int> stck;
    unordered_set<int> us;
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        for(int i = maxNumbers-1; i >= 0 ; --i) stck.push(i);
    }

    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if( stck.empty() ) return -1;
        int t = stck.top();
        stck.pop();
        us.insert(t);
        return t;
    }

    /** Check if a number is available or not. */
    bool check(int number) {
        return us.find(number) == us.end();
    }

    /** Recycle or release a number. */
    void release(int number) {
        auto f = us.find(number);
        if( f != us.end() ) {
            us.erase(f);
            stck.push(number);
        }
    }
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory* obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj->get();
 * bool param_2 = obj->check(number);
 * obj->release(number);
 */
