
// 1320. Minimum Distance to Type a Word Using Two Fingers
// https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/





// ABCDEFGHIJKLMNOPQRSTUVWXYZ
class Solution {
private:
    vector<vector<int>> keyboard = {{0,0},{0,1},{0,2},{0,3},{0,4},{0,5} // ABCDEF
                                   ,{1,0},{1,1},{1,2},{1,3},{1,4},{1,5} // GHIJKL
                                   ,{2,0},{2,1},{2,2},{2,3},{2,4},{2,5} // MNOPQR
                                   ,{3,0},{3,1},{3,2},{3,3},{3,4},{3,5} // STUVWX
                                   ,{4,0},{4,1}};                       // YZ

    int distances[27][27];

    //int mem[300][27][27];

    int rec(string& word, int n, int f1, int f2, int pos, int mem[][27][27]) {
        if( pos == n )
            return 0;

        /*
        // debug
        char cf1 = f1 == 26 ? '#' : f1+'A';
        char cf2 = f2 == 26 ? '#' : f2+'A';
        cout << "in  pos " << pos << " " << word[pos] << " f1 " << f1 << " " << cf1
             << " f2 " << f2 << " " << cf2 << endl;
        */

        if( mem[pos][f1][f2] != -1 )
            return mem[pos][f1][f2];

        // we have a choice: move finger 1 to the current letter or
        //    move finger 2 to the current letter
        int c = word[pos]-'A';
        int ans = min(distances[f1][c]+rec(word,n,c,f2,pos+1,mem),
                      distances[f2][c]+rec(word,n,f1,c,pos+1,mem));

        /*
        cout << "in  pos " << pos << " " << word[pos] << " f1 " << f1 << " " << cf1
             << " f2 " << f2 << " " << cf2 << " ans " << ans << endl;
        */
        return mem[pos][f1][f2] = ans;
    }

public:
    int minimumDistance(string word) {

        memset(distances,0,sizeof distances);
        int x1,y1,x2,y2,d;
        for(int i = 0; i < 26; ++i) {
            x1 = keyboard[i][0];
            y1 = keyboard[i][1];
            for(int j = 0; j < 26; ++j) {
                x2 = keyboard[j][0];
                y2 = keyboard[j][1];
                d = abs(x1-x2)+abs(y1-y2);
                distances[i][j] = d;
                distances[j][i] = d;
            }
        }

        int n = word.size();
        int mem[n][27][27];memset(mem,-1,sizeof mem);
        return rec(word,n,26,26,0,mem);
    }
};
