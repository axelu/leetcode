
// 767. Reorganize String
// https://leetcode.com/problems/reorganize-string/




class Solution {
public:
    string reorganizeString(string s) {
        int n = s.size();
        if( n == 1 )
            return s;
        if( n == 2 ) {
            return s[0] == s[1] ? "" : s;
        }


        // 358. Rearrange String k Distance Apart
        // https://leetcode.com/problems/rearrange-string-k-distance-apart/
        int k = 2;

        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char c : s)
            ++cnt[c-'a'];

        // array<int,3> charidx,count,lastseen
        auto cmp = [](const array<int,3>& a, const array<int,3>& b){
            if( a[1] < b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] > b[0] )
                    return true;
            }
            return false;
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);

        int distinct = 0;
        for(int i = 0; i < 26; ++i)
            if( cnt[i] > 0 ) {
                pq.push({i,cnt[i],INT_MIN});
                ++distinct;
            }

        // k is greater than the number of distinct letters we have
        if( k > distinct )
            return "";


        int i = 0,charidx,count,lastseen,j;
        queue<array<int,3>> park;
        while( i < n ) {

            for(j = 0; j < k; ++j) {
                charidx  = pq.top()[0];
                count    = pq.top()[1];
                lastseen = pq.top()[2];
                pq.pop();

                if( i < lastseen + k )
                    return "";

                s[i] = charidx+'a';
                --count;
                if( count > 0 )
                    park.push({charidx,count,i});
                ++i;
                if( pq.empty() )
                    break;
            }
            while( !park.empty() ) {
                pq.push(park.front());
                park.pop();
            }
        }


        return s;
    }
};
