
// Contains Duplicate III
// https://leetcode.com/problems/contains-duplicate-iii/



class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if( nums.empty() || nums.size() == 1 || k == 0 ) return false;

        // k <= absolute difference between i and j (Note: k has to be greater 0)
        // t <= absolute difference between nums[i] and nums[j] 
        
        size_t ns = nums.size();
        map<int,int> m; // keyed by num, value is index
        for(auto i = 0; i < ns; ++i) {
            // cout << "i " << i << " " << nums[i] << endl;
            auto p = m.insert({nums[i],i});
            if( !p.second ) {
                if( i - p.first->second <= k && t >= 0 )
                    return true;            
                p.first->second = i;
            }
            
            if( t > 0 ) {
                // left
                for(auto it = make_reverse_iterator(p.first); it != m.rend(); ++it) {
                    // cout << "left it " << it->first << endl;
                    if ((it->first < 0) && (nums[i] > INT_MAX + it->first)) 
                        // nums[i] - it->first would overflow and hence cannot be true
                        continue;
                    if ((it->first > 0) && (nums[i] < INT_MIN + it->first))
                        // nums[i] - it->first would underflow and hence cannot be true
                        continue;
                    if( abs(nums[i] - it->first) <= t && i - it->second <= k )
                        return true;
                }

                // right
                for(auto it = p.first; it != m.end(); ++it) {
                    if( it == p.first ) continue;
                    // cout << "right it " << it->first << endl;
                    if ((it->first < 0) && (nums[i] > INT_MAX + it->first)) 
                        // nums[i] - it->first would overflow and hence cannot be true
                        continue;
                    if ((it->first > 0) && (nums[i] < INT_MIN + it->first))
                        // nums[i] - it->first would underflow and hence cannot be true
                        continue;
                    if( abs(nums[i] - it->first) <= t && i - it->second <= k )
                        return true;
                }
            }
        }

        return false;   
    }
};
