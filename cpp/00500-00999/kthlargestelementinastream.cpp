
// 703. Kth Largest Element in a Stream
// https://leetcode.com/problems/kth-largest-element-in-a-stream/



class KthLargest {
private:
    multiset<int> ms;
    int K;
public:
    KthLargest(int k, vector<int>& nums) {
        K = k;
        for(int i = 0; i < nums.size(); ++i) {
            ms.insert(nums[i]);
            if( i >= k ) ms.erase(ms.begin());
        }
    }

    int add(int val) {
        ms.insert(val);
        if(ms.size() > K) ms.erase(ms.begin());
        return *ms.begin();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
