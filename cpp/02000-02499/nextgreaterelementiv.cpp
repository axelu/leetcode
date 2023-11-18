
// 2454. Next Greater Element IV
// https://leetcode.com/problems/next-greater-element-iv/




class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n,-1);
        if( n < 3 )
            return ans;

        /*
        // pass 1 next greater element
        vector<int> nxtgreater(n,-1); // index of next greater element to the right aka k
        stack<pair<int,int>> stck;
        for(int i = 0; i < n; ++i) {
            while( !stck.empty() && nums[i] > stck.top().first ) {
                nxtgreater[stck.top().second] = i;
                stck.pop();
            }
            stck.push({nums[i],i});
        }
        for(int i = 0; i < n; ++i)
            cout << i << ":" << nxtgreater[i] << " ";
        cout << endl;

        // pass 2
        // TODO we can create the list as part of pass 1 directly
        vector<int> ks[n]; // ks[k], list of indicies i for which k is the next greater element
        for(int i = 0; i < n; ++i) {
            int k = nxtgreater[i];
            if( k != -1 )
                ks[k].push_back(i);
        }
        */


        vector<int> ks[n]; // ks[k], list of indicies i for which k is the next greater element
        stack<pair<int,int>> stck;
        for(int i = 0; i < n; ++i) {
            while( !stck.empty() && nums[i] > stck.top().first ) {
                ks[i].push_back(stck.top().second);
                stck.pop();
            }
            stck.push({nums[i],i});
        }


        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            return a.first > b.first;
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> pq(cmp);
        for(int j = 1; j < n; ++j) {
            while( !pq.empty() && nums[j] > pq.top().first ) {
                ans[pq.top().second] = nums[j];
                pq.pop();
            }
            for(int i: ks[j])
                pq.push({nums[i],i});
        }

        return ans;
    }
};
