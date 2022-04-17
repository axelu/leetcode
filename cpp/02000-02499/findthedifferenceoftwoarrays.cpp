
// 2215. Find the Difference of Two Arrays
// https://leetcode.com/problems/find-the-difference-of-two-arrays/


class Solution {
private:
    // remove duplicates
    void removeDuplicates(vector<int>& arr) {
        // input is non-empty sorted vector<int>
        int n = arr.size();
        if( n == 1 )
            return;

        for(auto it = next(arr.begin()); it != arr.end(); )
            if( *prev(it) == *it )
                it = arr.erase(it);
            else
                ++it;
    }

public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(),nums1.end());removeDuplicates(nums1);
        sort(nums2.begin(),nums2.end());removeDuplicates(nums2);
        vector<int> a;
        vector<int> b;

        int t[2001];memset(t,0,sizeof t);
        for(int i = 0; i < nums2.size(); ++i)
            t[nums2[i]+1000] = 1;
        for(int i = 0; i < nums1.size(); ++i)
            if( !t[nums1[i]+1000] )
                a.push_back(nums1[i]);

        memset(t,0,sizeof t);
        for(int i = 0; i < nums1.size(); ++i)
            t[nums1[i]+1000] = 1;
        for(int i = 0; i < nums2.size(); ++i)
            if( !t[nums2[i]+1000] )
                b.push_back(nums2[i]);

        return {a,b};
    }
};
