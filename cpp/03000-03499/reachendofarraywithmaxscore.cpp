
// 3282. Reach End of Array With Max Score
// https://leetcode.com/problems/reach-end-of-array-with-max-score/

class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0LL;
        
        
        // hint
        // It can be proven that from each index i, the optimal solution is to jump to the nearest index j > i such that nums[j] > nums[i].
        // TODO look/get proof
        // how could I have come up with that intuition
        // could have only seen it via an observation
        // looking at other solutions, here is the explanations
        /* 
        class Solution {
            public long findMaximumScore(List<Integer> a) {
                int n = a.size();
                int max = 0;
                long ans = 0;
                for(int i = 0;i < n-1;i++){
                    int v = a.get(i);
                    max = Math.max(max, v);
                    ans += max;
                }
                return ans;
            }
	    }
        */
        // while we are traveling over each index, the maximum score is achieved
        // by taking the current max encountered at each step till we encounter a better one (read: new max)
        // duh
        
        // implementation based on hint
        
        // monotonically increasing stack
        int next_greater_idx[n]; memset(next_greater_idx,-1,sizeof next_greater_idx);
        
        stack<array<int,2>> stck;
        stck.push({nums[n-1], n-1});
        for(int i = n-2; i >= 0; --i) {
            int val = nums[i];
            
            while( !stck.empty() && stck.top()[0] <= val )
                stck.pop();
            
            if( !stck.empty() )
                next_greater_idx[i] = stck.top()[1];
            
            stck.push({nums[i], i});
        }
        
        long long ans = 0LL;
        
        for(int i = 0; ; ) {
            // if jump -1 then end
            if( next_greater_idx[i] != -1 ) {
                ans = ans + ((next_greater_idx[i] - i) * (long long)nums[i]);
                i = next_greater_idx[i];
            } else {
                ans = ans + (((n-1) - i) * (long long)nums[i]);
                break;
            }
        }
        
        return ans;
    }
};









// failing with TLE, both options

class Solution {
private:

    long long rec(vector<int>& nums, int n, int i, long long mem[]) {

        long long ret = 0LL;

        if( mem[i] != -1LL )
            return mem[i];

        // we have a choice
        //     jump to any index j with i < j < n

        for(int j = i+1; j < n; ++j) {

            // score for jump
            long long score = (j - i) * (long long)nums[i];
            long long t = rec(nums, n, j, mem);
            ret = max(ret, score + t);
        }

        return mem[i] = ret;
    }




public:
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size();

        // score for a jump from index i to index j is calculated as (j - i) * nums[i] with i > j
        long long mem[n]; memset(mem,-1,sizeof mem);
        // return rec(nums, n , 0, mem);


        // TODO try a Dijkstra, reverse all distances
    // min heap
    priority_queue<array<long long,2>,vector<array<long long,2>>,greater<array<long long,2>>> pq;

    // distances
    long long A[n];
    //for(int i = 0; i < n; ++i) A[i] = 1000000;
    memset(A,0,sizeof A);

    // push our source vertex into priority queue
    pq.push({0LL,0LL});
    // set distance to our source vertex itself to 0
    //A[s] = 0;

    long long weight;
    while(!pq.empty()) {

        int u = pq.top()[1];
        pq.pop();

        for(int v = u+1; v < n; ++v) {
            weight = (u-v) * (long long)nums[u];

            //  If there is shorter path to v through u.
            if( A[v] > A[u] + weight ) {
                // Updating distance of v
                A[v] = A[u] + weight;
                pq.push({A[v], v});
            }
        }
    }

    return -A[n-1];


    }
};
