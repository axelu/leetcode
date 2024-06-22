
// 2561. Rearranging Fruits
// https://leetcode.com/problems/rearranging-fruits/




class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        int n = basket1.size(); // basket1.size() == basket2.size()

        map<int,pair<int,int>> um;
        for(int i = 0; i < n; ++i) {
            ++um[basket1[i]].first;
            ++um[basket2[i]].second;
        }

        vector<long long> v; // elements to swap in asc order
        long long val_smallest;
        for(auto it = um.begin(); it != um.end(); ++it) {
            int x = it->first;
            int num_x_in_basket1 = it->second.first;
            int num_x_in_basket2 = it->second.second;
            int total_x = num_x_in_basket1 + num_x_in_basket2;

            // we can not distribute an odd count accross 2 baskets
            if( total_x % 2 == 1 )
                return -1;

            // how many do we need to swap
            int t = (total_x / 2) - min(num_x_in_basket1,num_x_in_basket2);
            for(int k = 0; k < t; ++k)
                v.push_back(x);

            if( it == um.begin() )
                val_smallest = x;
        }

        /*
        cout << "val_smallest " << val_smallest << endl;
        for(int i = 0; i < v.size(); ++i)
            cout << v[i] << " ";
        cout << endl;
        */

        // we have the smallest element val_smallest
        // we have two options:
        //     swap a small element with a big element for the cost of the small element OR
        //     utilize the smallest element twice to swap the small and big element for cost 2* val_smallest
        long long ans = 0;
        for(int i = 0; i < v.size()/2; ++i)
            ans += min(v[i], val_smallest * 2LL);

        return ans;
    }
};
