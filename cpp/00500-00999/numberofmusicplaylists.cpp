
// 920. Number of Music Playlists
// https://leetcode.com/problems/number-of-music-playlists/



class Solution {
private:
    long mod = 1000000007;
    int N, _goal, K;

    // returns factorial n mod 10^9 + 7
    long fact(int n) {
        long res = 1;
        for(long i = 2; i <= n; ++i)
            res = (res * i) % mod;
        return res;
    }

    long mem[100][100];

    long rec(int n, int goal, int k, int pos, int song) {
        // pos = idx in our playlist
        // song = song we are playing

        // cout << "rec pos " << pos << " song " << song << endl;

        if( song > n )
            return 0;

        if( pos == goal )
            return song == n; // have we played all songs, only then we have a solution

        if( mem[pos][song] != -1 )
            return mem[pos][song];

        // at each position in our playlist we have a choice
        //     play a song that has not been played yet next => new song
        //     play a song that has already played,
        //         in which case in can be played after k other songs => repeated song

        // new song
        // we can chose from the remaining songs if any: n-song
        long a = (rec(n,goal,k,pos+1,song+1) * (n-song)) %mod;

        // repeat song
        // we can chose from the songs all songs that come k songs before our current song if any
        long b = (rec(n,goal,k,pos+1,song) * max(0,song-k)) % mod;

        long t = (a + b) % mod;
        return mem[pos][song] = t;
    }

public:
    int numMusicPlaylists(int n, int goal, int k) {
        // n    = number of different songs we have
        // goal = length of desired play list
        // k    = song can only be played again if k other songs have been played

        // edge case
        if( n == goal )
            return fact(n);

        memset(mem,-1,sizeof mem);
        return rec(n,goal,k,0,0);
    }
};
