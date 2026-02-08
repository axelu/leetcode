
// 3785. Minimum Swaps to Avoid Forbidden Values
// https://leetcode.com/problems/minimum-swaps-to-avoid-forbidden-values/



class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        int n = nums.size(); // 1 <= n <= 1e5; nums.size() == forbidden.size()
        if( n == 1 )
            return nums[0] == forbidden[0] ? -1 : 0;

        // quick check
        // example    0 1 2 3 4 5 6 7 8 n = 9
        // forbidden  a a a a a c e f g
        // nums       a a a a e a f g d
        // we have a total of 5 a's in nums
        // we have 5 forbidden a's, hence we have n-5 = 4 allowed a's
        // so we know we have no solution

        unordered_map<int, vector<int>> must_swap;     // key: val; value: list of indices
        unordered_map<int, vector<int>> forbidden_dic; // key: val; value: list of indices
        unordered_map<int, vector<int>> nums_dic;      // key: val; value: list of indices
        for(int i = 0; i < n; ++i) {
            forbidden_dic[forbidden[i]].push_back(i);
            nums_dic[nums[i]].push_back(i);

            if( nums[i] == forbidden[i] )
                must_swap[nums[i]].push_back(i);
        }

        if( must_swap.empty() )
            return 0;

        // at minimum we must make must_swap.size()/2 swaps
        // if must_swap.size()/2 is odd, we must make at minimum 1 more

        // quick check
        for(auto& p: nums_dic) {
            int val = p.first;
            // p.second = indices with val
            int have = p.second.size();
            auto f = forbidden_dic.find(val);
            if( f != forbidden_dic.end() ) {
                int can_have = n - f->second.size();
                if( have > can_have )
                    return -1;
            }
        }

        int ans = 0;

        // edge case, must_swap.size() == 1
        // TODO

        // we will sort must_swap by count
        // we will swap the most with the second most one at a time
        // if we have left overs, we need to start swapping at
        //     indices that don't need swapping
        // example    0 1 2 3 n = 4
        // forbidden  a a b e
        // nums       a a b d
        // select i = 0 and j = 2 and swap, which leaves us with i = 1
        // we swap i = 1 and j = 3

        /*
        auto cmp = [](const pair<int,vector<int>>& a, const pair<int,vector<int>>& b){
            return a.second.size() < b.second.size();
        };
        priority_queue<pair<int,vector<int>>,vector<pair<int,vector<int>>>,decltype(cmp)> pq(cmp);
        for(auto& p: must_swap)
            pq.push(p);

        while( pq.size() > 1 ) {
            ++ans;

            auto most = pq.top();
            pq.pop();
            auto second_most = pq.top();
            pq.pop();

            // swap
            // int i = most.second.back();
            most.second.pop_back();
            // int j = second_most.second.back();
            second_most.second.pop_back();
            // we are swapping i and j

            if( !most.second.empty() )
                pq.push(most);
            if( !second_most.second.empty() )
                pq.push(second_most);
        }
        // what is left? we know we will be able to swap
        while( !pq.empty() ) {
            ans += pq.top().second.size();
            pq.pop();
        }
        */

        priority_queue<int> pq;
        for(auto& p: must_swap)
            pq.push(p.second.size());

        while( pq.size() > 1 ) {
            ++ans;

            int most = pq.top();
            pq.pop();
            int second_most = pq.top();
            pq.pop();

            // swap
            --most;
            --second_most;

            if( most != 0 )
                pq.push(most);
            if( second_most != 0 )
                pq.push(second_most);
        }
        // what is left? we know we will be able to swap
        while( !pq.empty() ) {
            ans += pq.top();
            pq.pop();
        }


        return ans;
    }
};
