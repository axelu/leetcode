
// 1024. Video Stitching
// https://leetcode.com/problems/video-stitching/



class Solution {
private:
    void print_clips(vector<vector<int>>& clips) {
        for(auto& vi : clips)
            cout << vi[0] << " " << vi[1] << ", ";
        cout << endl;
    }

    int rec(vector<vector<int>>& clips, int n, int pos, int time, int mem[]) {

        int curEnd = clips[pos][1];
        if( curEnd >= time )
            return 1;

        // shouldn't have to do this
        if( pos == n-1 && curEnd < time)
            return 101;

        if( mem[pos] != -1 )
           return mem[pos];

        int ret = 101;

        int curStart = clips[pos][0];
        int start,end;
        for(int i = pos + 1; i < n; ++i) {
            start = clips[i][0];
            end   = clips[i][1];

            // start cannot be less than curStart due to sorting
            if( start == curStart )
                continue;
            if( end <= curEnd ) // we do not gain anything
                continue;
            if( start > curEnd )
                break;

            ret = min(ret,1 + rec(clips,n,i,time,mem));
        }

        return mem[pos] = ret;
    }

public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        // base case
        if( clips.size() == 1 )
            return clips[0][0] > 0 || clips[0][1] < time ? -1 : 1;


        int mxEnd = INT_MIN; int * pMxEnd = &mxEnd;
        sort(clips.begin(),clips.end(),[pMxEnd,time] (const vector<int>& a, vector<int>& b) {
            if( a[0] < time )
                *pMxEnd = max(*pMxEnd,a[1]);
            if( b[0] < time )
                *pMxEnd = max(*pMxEnd,b[1]);

            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] )
                    return true;
            }
            return false;
        });
        // cout << "mxEnd " << mxEnd << endl;

        // no clip that starts before time and goes up to time or longer
        if( mxEnd < time )
            return -1;

        // remove from end where start >= time
        while( !clips.empty() && clips.back()[0] >= time )
            clips.pop_back();

        if( clips.empty() || clips[0][0] > 0 )
            return -1;

        // remove dups
        set<vector<int>> st;
        for(auto it = clips.begin(); it != clips.end(); ) {
            if ( st.find(*it) != st.end() ) {
                it = clips.erase(it);
            } else {
                st.insert(*it);
                ++it;
            }
        }

        if( clips.empty() )
            return -1;

        int n = clips.size();
        int ans = 101,t;
        int mem[n];memset(mem,-1,sizeof mem);
        for(int i = 0; i < n; ++i) {
            // run for every clip that starts at 0
            if( clips[i][0] > 0 )
                break;

            ans = min(ans,rec(clips,n,i,time,mem));
        }

        return ans == 101 ? -1 : ans;
    }
};
