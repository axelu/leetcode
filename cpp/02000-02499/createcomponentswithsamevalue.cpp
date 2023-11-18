
// 2440. Create Components With Same Value
// https://leetcode.com/problems/create-components-with-same-value/





class Solution {
private:
    vector<int> get_divisors(int n) {
        vector<int> v;
        stack<int> stck;
        for(int i = 1; i * i <= n; ++i)
            if(n % i == 0) {
                v.push_back(i);
                int q = n / i;
                if( q != i )
                    stck.push(q);
            }

        while( !stck.empty() ) {
            v.push_back(stck.top());
            stck.pop();
        }

        return v;
    }

    // DFS
    int rec(vector<int>& nums, vector<int> t[], int u, int target, bool seen[]) {
        seen[u] = true;

        int ret = nums[u];
        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( seen[v] )
                continue;
            ret += rec(nums,t,v,target,seen);
        }

        // if we can make the target sum, we will report up a result of 0 upwards
        if( ret == target )
            ret = 0;

        return ret;
    }


public:
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();

        // we cannot create a component whose sum is smaller than the greatest node value
        // we cannot create a components whose sum is not a divisor of the total sum
        // the number of components cannot be greater than the number of nodes

        int sum = 0;
        int max_node_value = 0;
        for(int val: nums) {
            sum += val;
            max_node_value = max(max_node_value,val);
        }

        // get divisors
        vector<int> divisors = get_divisors(sum);

        // undirected tree
        vector<int> t[n];
        for(auto& v: edges) {
            t[v[0]].push_back(v[1]);
            t[v[1]].push_back(v[0]);
        }

        // we arbitrarily will pick node 0 as root

        int divisors_sz = divisors.size();
        for(int i = divisors_sz - 1; i >= 0; --i) {
            // dividing the sum by divisor will give is the target sum for our components
            // the divisor represents the number of components
            // in order to create that number of components, we would have removed divisor-1 edges
            // because we are starting from the largest divisor, it will be the max
            // so once we have a solution, we are done

            if( divisors[i] > n )
                continue;

            int target = sum / divisors[i];
            if( target < max_node_value )
                continue;

            bool seen[n];memset(seen,false,sizeof seen);
            if( rec(nums,t,0,target,seen) == 0 )
                return divisors[i] - 1;
        }

        return 0;
    }
};
