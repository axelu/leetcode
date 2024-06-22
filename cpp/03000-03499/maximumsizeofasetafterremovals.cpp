
// 3002. Maximum Size of a Set After Removals
// https://leetcode.com/problems/maximum-size-of-a-set-after-removals/



class Solution {
public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // n == nums1.length == nums2.length, n % 2 == 0

        unordered_map<int,array<int,2>> um;
        int removed1 = 0;
        for(int x: nums1) {
            auto p = um.insert({x,{1,0}});
            if( !p.second )
                ++removed1;
        }
        int removed2 = 0;
        for(int x: nums2) {
            auto p = um.insert({x,{0,1}});
            if( !p.second ) {
                if( p.first->second[0] == 0 ) {
                    ++removed2;
                } else if( p.first->second[1] == 1 ) {
                    ++removed2;
                } else {
                    p.first->second[1] = 1;
                }
            }
        }
        //for(auto& p: um)
        //    cout << p.first << ":" << p.second[0] << "," << p.second[1] << " ";
        //cout << endl;
        //cout << "removed1 " << removed1 << endl;
        //cout << "removed2 " << removed2 << endl;

        // we preserved all unique elements found in nums1 and nums2
        // and already counted possible removals in nums1 and nums2
        // what is left for each unique element is either
        // it exists in only nums1 1 0
        // it exists in only nums2 0 1
        // or it exists in both    1 1
        // if it exists in both, and we still need to remove elements from either nums1 or nums2 we have a choice

        if( removed1 >= n/2 && removed2 >= n/2 ) {
            // no further removals needed
            return um.size();
        }

        if( removed1 >= n/2 && removed2 < n/2 ) {
            // we still need to remove elements from nums2
            for(auto& p: um)
                if( p.second[0] == 1 && p.second[1] == 1 )
                    ++removed2;
            return removed2 >= n/2 ? um.size() : um.size() - (n/2 - removed2);
        }

        if( removed1 < n/2 && removed2 >= n/2 ) {
            // we still need to remove elements from nums1
            for(auto& p: um)
                if( p.second[0] == 1 && p.second[1] == 1 )
                    ++removed1;
            return removed1 >= n/2 ? um.size() : um.size() - (n/2 - removed1);
        }

        // we still need to remove elements from nums1 and nums2
        int to_be_removed1 = n/2 - removed1; // cout << "to_be_removed1 " << to_be_removed1 << endl;
        int to_be_removed2 = n/2 - removed2; // cout << "to_be_removed2 " << to_be_removed2 << endl;
        for(auto& p: um) {
            if( p.second[0] == 1 && p.second[1] == 1 ) {
                if( to_be_removed1 > 0 && to_be_removed2 > 0 ) {
                    if( to_be_removed1 > to_be_removed2 )
                        --to_be_removed1;
                    else
                        --to_be_removed2;
                } else if(  to_be_removed1 > 0 ) {
                    --to_be_removed1;
                } else if(  to_be_removed2 > 0 ) {
                    --to_be_removed2;
                }
            }
        }

        return um.size() - to_be_removed1 - to_be_removed2;
    }
};
