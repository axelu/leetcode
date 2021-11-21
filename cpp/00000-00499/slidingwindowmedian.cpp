
// 480. Sliding Window Median
// https://leetcode.com/problems/sliding-window-median/




class Solution {
private:
    double o = 1e-9;
    double m;

    // max heap, stores the smaller half elements, left side
    multiset<int> l; // look at last element for max

    // min heap, stores the greater half elements, right side
    multiset<int> r;  // look at first element for min


    double addNum(int num) {
        if( l.size() > r.size() ) {
            // case 1: left side heap has more elements
            if( num < m ) {
                r.insert(*prev(l.end()));
                l.erase(prev(l.end()));
                l.insert(num);
            } else {
                r.insert(num);
            }
            // now even
            m = ((double)*prev(l.end()) + *r.begin())/2.0;
        } else if( l.size() == r.size() ) {
            // case 2: left and right heaps are balanced
            if( num < m ) {
                l.insert(num);
                m = *prev(l.end());
            } else {
                r.insert(num);
                m = *r.begin();
            }
        } else {
            // case 3: right side heap has more elements
            if( num > m ) {
                l.insert(*r.begin());
                r.erase(r.begin());
                r.insert(num);
            } else {
                l.insert(num);
            }
            // now even
            m = ((double)*prev(l.end()) + *r.begin())/2.0;
        }
        return m;
    }


    void removeNum(int num) {

        if( !l.empty() && num <= *prev(l.end()) ) {
            // num is in left half
            auto f = l.find(num);
            l.erase(f);
        } else if( !r.empty() && num >= *r.begin() ) {
            // num is in right half
            auto f = r.find(num);
            r.erase(f);
        }

        // balance
        if( l.size()+2 == r.size() ) {
            l.insert(*r.begin());
            r.erase(r.begin());
            // now even
            m = ((double)*prev(l.end()) + *r.begin())/2.0;
        } else if( r.size()+2 == l.size() ) {
            r.insert(*prev(l.end()));
            l.erase(prev(l.end()));
            // now even
            m = ((double)*prev(l.end()) + *r.begin())/2.0;
        } else if( l.size() > r.size() ) {
            m = *prev(l.end());
        } else if( r.size() > l.size() ) {
            m = *r.begin();
        } else {
           m = l.empty() ? DBL_MAX : ((double)*prev(l.end()) + *r.begin())/2.0;
        }

    }


public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();


        vector<double> ans(n-k+1);

        m = DBL_MAX;
        int w;                          // size of sliding window
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index
            m = addNum(nums[j]);

            w = j-i+1;
            if( w < k )
                continue;

            ans[i] = m;

            removeNum(nums[i]);

            ++i;
        }

        return ans;
    }
};
