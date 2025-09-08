
// 3614. Process String with Special Operations II
// https://leetcode.com/problems/process-string-with-special-operations-ii/





class Solution {
public:
    char processStr(string s, long long k) {
        int n = s.size(); // size of original string s

        // keep track of steps in which we encounter a char that we are adding
        // because we will later reverse the steps and halt at an add action
        vector<char> add(n);

        // first: action (0 remove last, 1 dup and append, 2 reverse, 3 append)
        // second: r_sz at time of action
        vector<pair<int,long long>> actions(n);

        long long r_sz = 0LL;
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if( c == '*' ) {
                // remove last char
                actions[i] = {0, r_sz};
                if( r_sz > 0 )
                    --r_sz;
            } else if( c == '#' ) {
                // duplicate and append
                actions[i] = {1, r_sz};
                r_sz *= 2LL;

            } else if( c == '%' ) {
                // reverse
                actions[i] = {2, r_sz};
                // reverse doesn't change size

            } else {
                actions[i] = {3, r_sz};
                add[i] = c;
                ++r_sz;
            }
        }

        // k is the position in result, hence r_sz - 1
        if( r_sz - 1 < k )
            return '.';

        // play back the actions in reverse
        // track the pos where the kth char appears 1st,
        int j = n-1;
        for( ; j >= 0; --j) {
            int action = actions[j].first;
            long long sz = actions[j].second; // size at time of action !!!

            // how does k change with the action?

            if( action == 0 ) {
                // 0 remove last
                // reversing the action appends the last char

            } else if( action == 1 ) {
                // 1 dup and append
                // reversing the action removes the second half of result !!!
                // so our current size is sz * 2 (after the action)
                if( k >= sz )
                    k -= sz;

            } else if( action == 2 ) {
                // 2 reverse
                k = (sz - 1LL) - k;

            } else {
                // 3 append
                // reversing the action removes the last char !!!
                // if our size here drops below k, we must stop
                // as we are tracking last time a char was added to pos
                // example test cases for that scenario
                // s = "qud#y" k = 6
                // s = "#%kp#k" k = 2
                if( sz == k )
                    break;
            }
        }

        return add[j];
    }
};
