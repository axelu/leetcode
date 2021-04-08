
// 346. Moving Average from Data Stream
// https://leetcode.com/problems/moving-average-from-data-stream/


class MovingAverage {
private:
    int sz;
    int sum;
    deque<int> dq;
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        sz = size;
        sum = 0;
    }

    double next(int val) {
        sum += val;
        dq.push_back(val);
        int n = dq.size();
        if( n > sz ) {
            sum -= dq.front();
            dq.pop_front();
            --n;
        }
        return (double)sum/(double)n;
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
