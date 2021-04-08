
// 170. Two Sum III - Data structure design
// https://leetcode.com/problems/two-sum-iii-data-structure-design/





class TwoSum {
private:
    multiset<long> ms;
public:
    /** Initialize your data structure here. */
    TwoSum() {
    }

    /** Add the number to an internal data structure.. */
    void add(int number) {
        ms.insert((long)number);
    }

    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        size_t n = ms.size();
        if( n <= 1 ) return false;
        if( n == 2 ) return *begin(ms) + *next(begin(ms)) == (long)value;

        for(auto it = begin(ms); it != end(ms); ++it) {
            int cnt = ms.count(value - *it);
            if( cnt > 0 ) {
                if( value % 2 == 0 ) {
                    if( *it != value/2 ) return true;
                    if( cnt > 1 ) return true;
                } else {
                    return true;
                }
            }
        }

        return false;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */
