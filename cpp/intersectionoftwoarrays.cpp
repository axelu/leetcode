
// 349. Intersection of Two Arrays
// https://leetcode.com/problems/intersection-of-two-arrays/



class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        vector<int> ans;
        if( n1 == 0 || n2 == 0 ) return ans;

        set<int> s;
        for(int i = 0; i < n1; ++i)
            s.insert(nums1[i]);

        sort(begin(nums2),end(nums2));
        if( nums2[0]     > *s.rbegin() ) return ans;
        if( nums2.back() < *s.begin()  ) return ans;
        for(int i = 0; i < n2; ++i)
            if( s.find(nums2[i]) != s.end() )
                if( ans.size() == 0 || ans.back() != nums2[i] )
                    ans.push_back(nums2[i]);

        return ans;
    }
};
