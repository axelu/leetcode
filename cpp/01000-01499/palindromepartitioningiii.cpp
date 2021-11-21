
// 1278. Palindrome partitioning III
// https://leetcode.com/problems/palindrome-partitioning-iii/



class Solution {
private:
    size_t N;
    int mem[101][101];
    char * S;
    int K;

    int cnt(int b, int e) {
        int ans = 0;
        while(b < e) {
            if( S[b] != S[e] ) ++ans;
            ++b;
            --e;
        }
        return ans;
    }

    int rec(int b, int partition) {
        if( b == N && partition == K ) return 0;
        if( partition >= K ) return N;

        if( mem[b][partition] != -1 ) return mem[b][partition];

        int minChanges = N; // worst case actually N/2
        int currChanges,afterChanges;
        for(int i = b; i < N; ++i) {
            currChanges  = cnt(b,i);
            afterChanges = rec(i+1,partition+1);
            minChanges = min(minChanges,currChanges + afterChanges);
        }

        return mem[b][partition] = minChanges;
    }



public:
    int palindromePartition(string s, int k) {
        N = s.size();
        if( N == 1 ) return 0;
        if( N == k ) return 0;
        S = s.data();
        if( k == 1 ) return cnt(0,N-1);
        K = k;

        for(int i = 0; i <=100; ++i)
            for(int j = 0; j <= 100; ++j)
                mem[i][j] = -1;

        return rec(0,0);
    }
};
