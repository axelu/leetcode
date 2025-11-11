
// 3744. Find Kth Character in Expanded String
// https://leetcode.com/problems/find-kth-character-in-expanded-string/



class Solution {
public:
    char kthCharacter(string s, long long k) {
        int s_sz = s.size(); // 1 <= s_sz <= 1e5

        // s does not contain any leading or trailing spaces.

        vector<pair<long long,char>> v; // {{starting idx of char, char}, ...}
        long long runidx = 0LL;
        long long charidx = 1;
        for(int i = 0; i < s_sz; ++i) {
            if( s[i] == ' ' ) {
                v.push_back({runidx, ' '});
                ++runidx;
                charidx = 1LL;
                continue;
            }

            // optimization
            // when we have consecutive chars, we can keep going
            if( i == 0 || s[i] != s[i-1] )
                v.push_back({runidx, s[i]});
            // the current char repeats chridx times
            runidx += charidx;
            ++charidx;
        }

        // binary search lower bound
        int n = v.size();
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int b = 0;
        int e = n; // n = nums.size()
        int mid;
        while(b < e) {
            mid = b + ((e-b)/2);
            if( k <= v[mid].first )
                e = mid;
            else
                b = mid+1;
        }
        if( b < n && v[b].first < k )
            ++b;

        if( b == n )
            return v[n-1].second;

        if( v[b].first > k )
            --b;

        return v[b].second;
    }
};
