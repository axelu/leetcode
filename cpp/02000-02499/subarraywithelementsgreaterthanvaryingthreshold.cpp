
// 2334. Subarray With Elements Greater Than Varying Threshold
// https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/

class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        int n = nums.size();
        
        vector<pair<int,int>> v(n); // value,i
        
        for(int i = 0; i < n; ++i)
            v[i] = {nums[i],i};
        
        sort(v.begin(),v.end(),[](const pair<int,int>& a, const pair<int,int>& b){
            if( a.first > b.first ) {
                return true;
            } else if( a.first == b.first ) {
                if( a.second < b.second ) {
                    return true;
                }
            }
            return false;
        });
            
        map<int,int> mp; // intervals start,end
        // interval merge
        int i = 0;
        for(int k = 1; k <= n; ++k) {
            // k is our length
            int t = (threshold/k) + 1;
            
            // add all elements >= to intervals 
            while( i < n && v[i].first >= t ) {
                int idx = v[i].second;
                // as all indexes are unique, we will always be able to insert
                auto f = mp.insert({idx,idx}).first; 
                // check if we can combine with left
                if( f != mp.begin() ) {
                    int lft_end = prev(f)->second;
                    if( lft_end + 1 == idx ) {
                        // combine
                        auto lft = prev(f);
                        lft->second = idx;
                        mp.erase(f);
                        f = lft;
                    }
                }
                // check if we can combine with right
                if( next(f) != mp.end() ) {
                    int rgt_start = next(f)->first;
                    if( idx + 1 == rgt_start ) {
                        // combine
                        f->second = next(f)->second;
                        mp.erase(next(f));
                    }
                }
                // is f an interval with length greater >= k ?
                if( f->second - f->first + 1 >= k ) 
                    return k;
                ++i;
            }
        }
        
        return -1;
    }
};
