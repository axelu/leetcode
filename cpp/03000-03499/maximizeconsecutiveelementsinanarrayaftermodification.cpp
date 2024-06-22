
// 3041. Maximize Consecutive Elements in an Array After Modification
// https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/



class Solution {
private:
    
    int rec(vector<pair<int,int>>& nums, int n, int i, int src, int mem[][3]) {
        // 0 <= src <= 2; 0: we are starting, 1: source not elevated, 2: source elevated
        // cout << "rec i " << i << " src " << src << endl;

        if( i == n )
            return 0;
  
        if( mem[i][src] != -1 )
            return mem[i][src];
        
        int a = 0;
        int b = 0;
        
        if( src == 0 ) {
            // we are just starting out
            int ret = nums[i].second == 1 ? 1 : 2;
            a = ret + rec(nums, n, i+1, 1, mem);
            b =   1 + rec(nums, n, i+1, 2, mem);
        
        } else {
            // can we connect to the source ?
            int pre = nums[i-1].first + (src - 1);
            if( nums[i].first + 1 == pre ) {
                a = 1 + rec(nums, n, i+1, 1, mem);
            
            } else if( nums[i].first + 2 == pre ) {
                a = 1 + rec(nums, n, i+1, 2, mem);
                if( nums[i].second > 1 )
                    b = 2 + rec(nums, n, i+1, 1, mem);;
            }
        }
            
        return mem[i][src] = max(a, b);
    }
    
public:
    int maxSelectedElements(vector<int>& nums) {
        map<int,int> mp;
        for(int x: nums)
            ++mp[x];

        /*
        for(auto it = mp.rbegin(); it != mp.rend(); ++it)
            cout << it->first << ":" << it->second << " ";
        cout << endl;
        */
        
        int n = mp.size();
        if( n == 1 )
            return mp.begin()->second == 1 ? 1 : 2;
        
        vector<pair<int,int>> _nums(n);
        int i = 0;
        for(auto it = mp.rbegin(); it != mp.rend(); ++it)
            _nums[i++] = {it->first,it->second};
            
        int ans = 0;
        int mem[n][3]; memset(mem, -1, sizeof mem);
        for(int i = 0; i < n && ans <= n-i+1; ++i)
            ans = max(ans, rec(_nums, n, i, 0, mem));
        
        return ans;
    }
};
