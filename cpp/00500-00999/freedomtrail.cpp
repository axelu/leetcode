
// 514. Freedom Trail
// https://leetcode.com/problems/freedom-trail/





class Solution {
private:

    int mem[100][100];

    int rec(string& ring, string& key, int ringPos, int keyPos) {
        // cout << "rec ringPos " << ringPos << " keyPos " << keyPos << endl;
        if( keyPos == key.size() )
            return 0;

        if( mem[ringPos][keyPos] != -1 ) {
            return mem[ringPos][keyPos];
        }

        int ret = INT_MAX;

        // current position in ring
        if( ring[ringPos] == key[keyPos] )
            ret = 1 + rec(ring,key,ringPos,keyPos+1);


        // at each step we can go clockwise and anticlockwise

        int rn = ring.size();
        int ringPos_new;

        // clockwise
        int kmax = rn/2;
        for(int k = 1; k <= kmax; ++k) {
            ringPos_new = ringPos+k;
            if( ringPos_new >= rn )
                ringPos_new %= rn;

            // cout << "clockwise ringPos_new     " << ringPos_new << endl;

            if( ring[ringPos_new] == key[keyPos] )
                ret = min(ret,1 + k + rec(ring,key,ringPos_new,keyPos+1));
        }
        // anticlockwise
        kmax = rn%2 == 0 ? rn/2-1 : rn/2;
        for(int k = 1; k <= kmax; ++k) {
            ringPos_new = ringPos-k;
            if( ringPos_new < 0 )
                ringPos_new += rn;

            // cout << "anticlockwise ringPos_new " << ringPos_new << endl;

            if( ring[ringPos_new] == key[keyPos] )
                ret = min(ret,1 + k + rec(ring,key,ringPos_new,keyPos+1));
        }

        return mem[ringPos][keyPos] = ret;
    }



public:
    int findRotateSteps(string ring, string key) {

        for(int i = 0; i < 100; ++i)
            for(int j = 0; j < 100; ++j)
                mem[i][j] = -1;

        return rec(ring,key,0,0);
    }
};
