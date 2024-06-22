
// 3144. Minimum Substring Partition of Equal Character Frequency
// https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/





class Solution {
private:

    int rec(string& s, int n, int pos, int mem[]) {
        if( pos == n )
            return 0;
        if( pos == n-1 )
            return 1;

        if( mem[pos] != -1 )
            return mem[pos];

        int ret = n - pos; // worst case

        unordered_map<char, int> cnt;
        for(int i = pos; i < n; ++i) {
            ++cnt[s[i]];
            // is our substring [pos,i] balanced?
            int t = cnt.begin()->second;
            bool is_balanced = true;
            for(auto it = next(cnt.begin()); it != cnt.end(); ++it) {
                if( it->second != t ) {
                    is_balanced = false;
                    break;
                }
            }
            if( is_balanced ) {
                ret = min(ret, 1 + rec(s, n, i+1, mem));
            }
        }

        return mem[pos] = ret;
    }



public:
    int minimumSubstringsInPartition(string s) {
        // definition:
        // A balanced string is a string where each character in the string occurs the same number of times.

        int n = s.size();
        int mem[n];memset(mem,-1,sizeof mem);
        return rec(s, n, 0, mem);
    }
};
