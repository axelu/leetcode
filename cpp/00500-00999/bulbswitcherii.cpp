
// 672. Bulb Switcher II
// https://leetcode.com/problems/bulb-switcher-ii/



class Solution {
private:
    void printVBool(vector<bool>& b, int n) {
        for(int i = 0; i <= n; ++i)
            cout << b[i];
        cout << endl;
    }

    void flipAll(vector<bool>& b, int n) {
        b.flip();b[0] = false;
    }

    void flipEven(vector<bool>& b, int n) {
        for(int i = 1; i <= n; ++i)
            if( !(i & 1) )
                b[i] = !b[i];
    }

    void flipOdd(vector<bool>& b, int n) {
        for(int i = 1; i <= n; ++i)
            if( i & 1 )
                b[i] = !b[i];
    }

    void flip3kplus1(vector<bool>& b, int n) {
        // j = 3k + 1 where k = 0, 1, 2, ...
        for(int k = 0; k < 334; ++k) {
            int j = 3 * k + 1;
            if( j > n )
                break;
            b[j] = !b[j];
        }
    }

public:
    int flipLights(int n, int presses) {
        if( presses == 0 )
            return 1;

        vector<bool> b(n+1,true);

        unordered_set<vector<bool>> seen[presses+1];

        // BFS
        queue<pair<vector<bool>,int>> q;
        q.push({b,0});
        while( !q.empty() ) {
            auto [v,step] = q.front();
            q.pop();

            if( step == presses )
                break;

            flipAll(v,n);
            //printVBool(v,n);
            if( !seen[step+1].count(v) ) {
                seen[step+1].insert(v);
                q.push({v,step+1});
            }
            flipAll(v,n); // backtrack

            flipEven(v,n);
            //printVBool(v,n);
            if( !seen[step+1].count(v) ) {
                seen[step+1].insert(v);
                q.push({v,step+1});
            }
            flipEven(v,n); // backtrack

            flipOdd(v,n);
            //printVBool(v,n);
            if( !seen[step+1].count(v) ) {
                seen[step+1].insert(v);
                q.push({v,step+1});
            }
            flipOdd(v,n); // backtrack

            flip3kplus1(v,n);
            //printVBool(v,n);
            if( !seen[step+1].count(v) ) {
                seen[step+1].insert(v);
                q.push({v,step+1});
            }
            // flip3kplus1(v,n);
        }

        return seen[presses].size();
    }
};
