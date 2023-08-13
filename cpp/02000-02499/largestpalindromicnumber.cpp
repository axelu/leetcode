
// 2384. Largest Palindromic Number
// https://leetcode.com/problems/largest-palindromic-number/



class Solution {
public:
    string largestPalindromic(string num) {
        int n = num.size();

        int cnt[10];memset(cnt,0,sizeof cnt);
        auto cmp = [](array<int,2>&a, array<int,2>& b) {
            if( a[1] < b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] < b[0] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        for(int i = 0; i < n; ++i) {
            int digit = num[i]-'0';
            ++cnt[digit];
            if( cnt[digit] == 2 ) {
                pq.push({digit,2});
                cnt[digit] = 0;
            }
        }
        for(int i = 0; i < 10; ++i)
            if( cnt[i] == 1 )
                pq.push({i,1});

        string ans = "";
        stack<int> stck;
        bool have_single = false;
        while( !pq.empty() ) {
            // when we add the largest single, we are done
            if( pq.top()[1] == 1 ) {
                have_single = true;
                ans.push_back(pq.top()[0]+'0');
                break;
            }

            if( pq.top()[0] == 0 && ans.size() == 0 ) {
                // we cannot have leading zeros
            } else {
                ans.push_back(pq.top()[0]+'0');
                stck.push(pq.top()[0]);
            }
            pq.pop();
        }
        // finish up
        while( !stck.empty() ) {
            ans.push_back(stck.top()+'0');
            stck.pop();
        }
        if( ans.size() == 0 )
            ans = "0";

        return ans;
    }
};
