
// 1865. Finding Pairs With a Certain Sum
// https://leetcode.com/problems/finding-pairs-with-a-certain-sum/




class FindSumPairs {
private:
    int * pNums1;
    int * pNums2;
    int n1;
    unordered_map<int,int> um;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        pNums1 = nums1.data();
        n1 = nums1.size();
        pNums2 = nums2.data();

        pair<unordered_map<int,int>::iterator,bool> p;
        for(int i = 0; i < nums2.size(); ++i) {
            p = um.insert({nums2[i],1});
            if( !p.second )
                ++p.first->second;
        }

    }

    void add(int index, int val) {
        int currVal = pNums2[index];
        auto f = um.find(currVal);
        // the current val has to be there
        --f->second;
        int newVal = pNums2[index] + val;
        // update
        pNums2[index] = newVal;
        auto p = um.insert({newVal,1});
        if( !p.second )
            ++p.first->second;
    }

    int count(int tot) {
        int ans = 0;
        unordered_map<int,int>::iterator f;
        for(int i = 0; i < n1; ++i) {
            f = um.find(tot-pNums1[i]);
            if( f != um.end() )
                ans += f->second;
        }
        return ans;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
