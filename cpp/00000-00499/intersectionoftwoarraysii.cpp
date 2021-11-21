
// 350. Intersection of Two Arrays II
// https://leetcode.com/problems/intersection-of-two-arrays-ii/



class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        vector<int> ans;
        if( n1 == 0 || n2 == 0 ) return ans;

        unordered_map<int,pair<int,int>> um;
        pair<unordered_map<int,pair<int,int>>::iterator,bool> p;
        for(int i = 0; i < n1; ++i) {
            p = um.insert({nums1[i],{1,0}});
            if( !p.second )
                ++p.first->second.first;
        }
        unordered_map<int,pair<int,int>>::iterator f;
        unordered_map<int,pair<int,int>>::iterator e = um.end();
        for(int i = 0; i < n2; ++i) {
            f = um.find(nums2[i]);
            if( f != e )
               ++f->second.second;
        }

        for(auto it = begin(um); it != e; ++it) {
            if( it->second.second != 0 ) {
                int n = min(it->second.first,it->second.second);
                for(int i = 0; i < n; ++i)
                    ans.push_back(it->first);
            }
        }

        return ans;
    }
};
