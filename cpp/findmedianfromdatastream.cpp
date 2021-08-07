
// 295. Find Median from Data Stream
// https://leetcode.com/problems/find-median-from-data-stream/
// day 11 July 2021 challenge
// https://leetcode.com/explore/featured/card/july-leetcoding-challenge-2021/609/week-2-july-8th-july-14th/3810/





class MedianFinder {
private:
    double o = 1e-9;
    double m;

    // max heap, stores the smaller half elements, left side
    priority_queue<int> l;

    // min heap, stores the greater half elements, right side
    priority_queue<int,vector<int>,greater<int> > r;


public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int k) {

        if( l.size() > r.size() ) {
            // case 1: left side heap has more elements
            if( k < m ) {
                r.push(l.top());
                l.pop();
                l.push(k);
            } else {
                r.push(k);
            }
            // now even
            m = (l.top() + r.top())/2.0;
        } else if( l.size() == r.size() ) {
            // case 2: left an right heaps are balanced
            if( k < m ) {
                l.push(k);
                m = l.top();
            } else {
                r.push(k);
                m = r.top();
            }
        } else {
            // case 3: right side heap has more elements
            if( k > m ) {
                l.push(r.top());
                r.pop();
                r.push(k);
            } else {
                l.push(k);
            }
            // now even
            m = (l.top() + r.top())/2.0;
        }

    }

    double findMedian() {
        return m;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
