
// 3316. Find Maximum Removals From Source String
// https://leetcode.com/problems/find-maximum-removals-from-source-string/

class Solution {
private:
    vector<int> nxt[3000][26];
    int mem[3000][3000];

    int rec(string& source, int i, string& pattern, int j, bool targetIdxs[]) {
        // cout << "rec i " << i << " j " << j << endl;
        int n = source.size();
        int p_sz = pattern.size(); // 1 <= pattern.length <= n

        // i index in source
        // j index in pattern
        // we will only be at a combination of i and j if source[i] == pattern[j]
        // if i is in target indicies, we have a cost of 1, otherwise we have a cost of 0

        if( mem[i][j] != -1 )
            return mem[i][j];


        int remaining_chars_in_source = n - i;
        int remaining_chars_in_pattern = p_sz - j;
        // its a little flawed as we are not accounting for chars in source that don't even exist in pattern
        if( remaining_chars_in_source < remaining_chars_in_pattern )
            return mem[i][j] = 10000;

        int cost = targetIdxs[i]; // if we are starting out, we could not bypass

        // if( j == p_sz-1 )
        //    return mem[i][j] = cost;

        int ret = 10000;

        // we have a choice
        //     don't use the current position in source if we can OR
        //     use the current position in source

        // TODO think about if we should even skip if not in targetIndices

        int curchar = source[i] - 'a';
        if( !nxt[i][curchar].empty() && cost == 1 ) {
            // cout << "rec i " << i << " j " << j << " can skip" << endl;
            ret = min(ret, rec(source, nxt[i][curchar][0], pattern, j, targetIdxs));

        }

        // peek
        if( j < p_sz-1 ) {
            int nxtcharinpattern = pattern[j+1] - 'a';
            if( !nxt[i][nxtcharinpattern].empty() )
                ret = min(ret, cost + rec(source, nxt[i][nxtcharinpattern][0], pattern, j+1, targetIdxs));
        } else {
            ret = min(ret, cost);
        }

        return mem[i][j] = ret;
    }

public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        int n = source.size(); // cout << "n " << n << endl;
        int p_sz = pattern.size(); // cout << "p_sz " << p_sz << endl; // 1 <= pattern.length <= n
        // targetIndices is sorted asc

        if( n == 1 )
            return 0;

        // optimization
        //    we could remove all chars from source that don't even exist in pattern
        //    we would need to update targetIndices accordingly

        // at each pos of source, record the next occurence of each char

        for(int i = n-2; i >= 0; --i) {
            int nxtchr = source[i+1] - 'a';
            for(int k = 0; k < 26; ++k) {
                nxt[i][k] = nxt[i+1][k];
                if( k == nxtchr )
                    nxt[i][k].insert(nxt[i][k].begin(), i+1);
                else
                    nxt[i][k] = nxt[i+1][k];
            }
        }

        bool targetIdxs[n];memset(targetIdxs,false,sizeof targetIdxs);
        for(int i: targetIndices)
            targetIdxs[i] = true;

        memset(mem,-1,sizeof mem);

        int ans = 10000;
        for(int i = 0; i <= n-p_sz; ++i) {
            if( source[i] == pattern[0] ) {
                // cout << "starting i " << i << endl;
                ans = min(ans, rec(source, i, pattern, 0, targetIdxs));
            }
        }

        return targetIndices.size() - ans;
    }
};



// passes 751/755 test cases, then TLE as of 10/16/2024


class Solution {
private:
    vector<int> nxt[3000][26];
    int mem[3000][3000];
    
    int rec(string& source, int i, string& pattern, int j, bool targetIdxs[]) {
        // cout << "i " << i << " j " << j << endl;
        int n = source.size();
        int p_sz = pattern.size(); // 1 <= pattern.length <= n
        
        // i index in source
        // j index in pattern
        // we will only be at a combination of i and j if source[i] == pattern[j]
        // if i is in target indicies, we have a cost of 1, otherwise we have a cost of 0
        
        if( mem[i][j] != -1 )
            return mem[i][j];
        
        
        int remaining_chars_in_source = n - i;
        int remaining_chars_in_pattern = p_sz - j;
        // its a little flawed as we are not accounting for chars in source that don't even exist in pattern
        if( remaining_chars_in_source < remaining_chars_in_pattern )
            return mem[i][j] = 10000;
        
        int cost = targetIdxs[i]; // if we are starting out, we could not bypass
        
        if( j == p_sz-1 )
            return mem[i][j] = cost;
        
        int ret = 10000;
        
        // peek
        int nxtcharinpattern = pattern[j+1] - 'a';
        for(auto it = nxt[i][nxtcharinpattern].begin(); it != nxt[i][nxtcharinpattern].end(); ++it) {
            ret = min(ret, cost + rec(source, *it, pattern, j+1, targetIdxs));
        }
        
        return mem[i][j] = ret;
    }
    
public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        int n = source.size();
        int p_sz = pattern.size(); // 1 <= pattern.length <= n
        // targetIndices is sorted asc
        
        if( n == 1 )
            return 0;
        
        // optimization
        //    we could remove all chars from source that don't even exist in pattern
        //    we would need to update targetIndices accordingly
            
        // at each pos of source, record the next occurence of each char

        for(int i = n-2; i >= 0; --i) {
            int nxtchr = source[i+1] - 'a';
            for(int k = 0; k < 26; ++k) {
                nxt[i][k] = nxt[i+1][k];
                if( k == nxtchr )
                    nxt[i][k].insert(nxt[i][k].begin(), i+1);
                else
                    nxt[i][k] = nxt[i+1][k];
            }
        }
        
        bool targetIdxs[n];memset(targetIdxs,false,sizeof targetIdxs);
        for(int i: targetIndices)
            targetIdxs[i] = true;
        
        memset(mem,-1,sizeof mem);
        
        int ans = 10000;
        for(int i = n-p_sz; i >= 0; --i) {
            if( source[i] == pattern[0] )
                ans = min(ans, rec(source, i, pattern, 0, targetIdxs));
        }
        
        return targetIndices.size() - ans;
    }
};
