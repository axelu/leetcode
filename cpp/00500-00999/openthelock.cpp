
// 752. Open the Lock
// https://leetcode.com/problems/open-the-lock/



class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        int seen[10000]; memset(seen,0,sizeof seen);
        for(int i = 0; i < deadends.size(); ++i)
            seen[stoi(deadends[i])] = 1;
        if( seen[0] ) return -1; // "0000" is a deadend, so we cannot get even started
        if( target == "0000" ) return 0;

        // BFS
        queue<pair<string,int>> q;
        q.push({"0000",0});
        seen[0] = 1;
        string s,t1,t2;
        int m;
        while(!q.empty()) {
            s = q.front().first;
            m = q.front().second;
            q.pop();
            for(int i = 0; i < 4; ++i) {
                t1 = s;
                t1[i] = t1[i] == '9' ? '0' : ((t1[i]-'0')+1)+'0';
                if( t1 == target ) return m+1;
                if( !seen[stoi(t1)] ) {
                    seen[stoi(t1)] = 1;
                    q.push({t1,m+1});
                }
                t2 = s;
                t2[i] = t2[i] == '0' ? '9' : ((t2[i]-'0')-1)+'0';
                if( t2 == target ) return m+1;
                if( !seen[stoi(t2)] ) {
                    seen[stoi(t2)] = 1;
                    q.push({t2,m+1});
                }
            }
        }
        return -1;
    }
};
