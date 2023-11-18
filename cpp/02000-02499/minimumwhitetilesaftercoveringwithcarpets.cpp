
// 2209. Minimum White Tiles After Covering With Carpets
// https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/





class Solution {
private:
    // binary search lower bound
    int lb(vector<int>& nums, int s, int e, int target) {
        int n = nums.size();
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        // int s = 0;
        // int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

    int mem[1000][1001];

    int rec(vector<int>& jump, int n, int i, int k) {
        // k = number carpets left
        if( i == n )
            return 0;

        if( k == 0 ) {
            // we have no more carpets left
            // return how many white tiles are to our right including the current tile
            return n-i;
        }
        if( k >= n-i ) {
            // we have enough carpets left to cover all white tiles
            // to our right including the current tile
            return 0;
        }

        if( mem[i][k] != -1 )
            return mem[i][k];

        // we have a choice
        //    don't use a carpet on the current white tile and go to the next white tile OR
        //    use a carpet and go to the next uncovered white tile

        int a = 1 + rec(jump,n,i+1,k);

        int b = rec(jump,n,jump[i],k-1);

        return mem[i][k] = min(a,b);
    }

public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int n = floor.size(); // floor[i] = '0' black tile, floor[i] = '1' white tile
        if( carpetLen == n )
            return 0;

        vector<int> white_tiles;
        for(int i = 0; i < n; ++i)
            if( floor[i] == '1' )
                white_tiles.push_back(i);

        if( white_tiles.empty() )
            return 0;

        int white_tiles_sz = white_tiles.size();
        if( numCarpets >= white_tiles_sz )
            return 0;

        // distance between 1st and last white tile inclusive
        int dist = white_tiles.back() - white_tiles.front() + 1;
        if( carpetLen >= dist )
            return 0;

        // lets calculate the next uncovered white tile to jump to
        // if we would cover a given white tile with a carpet
        vector<int> jump(white_tiles_sz,white_tiles_sz);
        for(int i = 0; i < white_tiles_sz - 1; ++i) {

            int target = white_tiles[i] + carpetLen;
            if( target > white_tiles.back() )
                break;

            jump[i] = lb(white_tiles,i,white_tiles_sz,target);
            if( jump[i] == white_tiles_sz )
                break;
        }
        /*
        for(int i = 0; i < white_tiles_sz; ++i) {
            cout << i << ":" << white_tiles[i] << ":" << jump[i] << " ";
        }
        cout << endl;
        */

        memset(mem,-1,sizeof mem);
        return rec(jump,white_tiles_sz,0,numCarpets);
    }
};
