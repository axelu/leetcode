
// 3189. Minimum Moves to Get a Peaceful Board
// https://leetcode.com/problems/minimum-moves-to-get-a-peaceful-board/





class Solution {
private:

    int solve (int n, int cnt[]) {
        int ret = 0;

        map<int,int> mp;
        stack<int> stck;

        for(int k = 0; k < n; ++k) {
            if( cnt[k] == 0 ) {
                stck.push(k);
            } else if( cnt[k] != 1 ) {
                mp[k] = cnt[k];
            }
        }

        while( !stck.empty() ) {
            int t = stck.top();
            stck.pop();

            auto f = mp.upper_bound(t);
            if( f != mp.end() ) {
                ret += f->first - t;
                --f->second;
                if( f->second == 1 )
                    mp.erase(f);
            } else {
                --f;
                ret += t - f->first;
                --f->second;
                if( f->second == 1 )
                    mp.erase(f);
            }
        }

        return ret;
    }

public:
    int minMoves(vector<vector<int>>& rooks) {
        int n = rooks.size();

        // if a row has 0 rooks, then
        // move a rook from the closest row that has a rook into that row

        int rcnt[n];memset(rcnt,0,sizeof rcnt);
        int ccnt[n];memset(ccnt,0,sizeof ccnt);
        for(int k = 0; k < n; ++k) {
            ++rcnt[rooks[k][0]];
            ++ccnt[rooks[k][1]];
        }

        int ans = 0;

        ans += solve(n, rcnt);
        ans += solve(n, ccnt);

        return ans;
    }
};
