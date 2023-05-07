
// 2526. Find Consecutive Integers from a Data Stream
// https://leetcode.com/problems/find-consecutive-integers-from-a-data-stream/



class DataStream {
private:
    int value;
    int k;
    int cnt;
public:
    DataStream(int value, int k) {
        this->value = value;
        this->k = k;
        cnt = 0;
    }

    bool consec(int num) {
        if( num == value ) {
            ++cnt;
            if( cnt == k ) {
                --cnt;
                return true;
            }
        } else {
            cnt = 0;
        }

        return false;
    }
};

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */
