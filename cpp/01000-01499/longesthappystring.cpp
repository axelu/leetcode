
// 1405. Longest Happy String
// https://leetcode.com/problems/longest-happy-string/



class Solution {
public:
    string longestDiverseString(int a, int b, int c) {

        //                a,b,c
        int con_cnt[3] = {0,0,0}; // consecutive count

        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            return a.first < b.first;
        };

        priority_queue<pair<int,char>,vector<pair<int,char>>,decltype(cmp)> pq(cmp);
        if( a > 0 )
            pq.push({a,0});
        if( b > 0 )
            pq.push({b,1});
        if( c > 0 )
            pq.push({c,2});

        string ans = "";

        while( !pq.empty() ) {

            vector<pair<int,char>> park;
            bool f = false;

            while( !pq.empty() && !f ) {
                auto p = pq.top();
                pq.pop();

                if( con_cnt[p.second] < 2 ) {
                    ans += (p.second + 'a');
                    ++con_cnt[p.second];
                    f = true;
                    --p.first;
                    if( p.first > 0 )
                        pq.push(p);
                    for(int i = 0; i < 3; ++i) {
                        if( i == p.second )
                            continue;
                        con_cnt[i] = 0;
                    }
                } else {
                    park.push_back(p);
                }
            }

            if( !f )
                break;

            for(auto& t: park)
                pq.push(t);
        }

        return ans;
    }
};
