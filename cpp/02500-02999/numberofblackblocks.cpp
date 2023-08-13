
// 2768. Number of Black Blocks
// https://leetcode.com/problems/number-of-black-blocks/




class Solution {
public:
    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) {
        // m rows, n cols
        long long total_blocks = (m-1LL) * (n-1LL);
        vector<long long> ans{total_blocks,0LL,0LL,0LL,0LL};
        int coordinates_sz = coordinates.size();
        if( coordinates_sz == 0 )
            return ans;


        sort(coordinates.begin(),coordinates.end());

        unordered_map<int,unordered_set<int>> um;
        for(int k = 0; k < coordinates.size(); ++k)
            um[coordinates[k][0]].insert(coordinates[k][1]);

        unordered_set<long> processed;
        for(int k = 0; k < coordinates.size(); ++k) {
            long x = coordinates[k][0];
            long y = coordinates[k][1];

            // we will check for sure as if [x,y] is the top-left corner of a block
            if( x < m-1 && y < n-1 ) {
                long key = (x<<17) + y;
                processed.insert(key);
                long long t = 1LL;
                if( um[x].find(y+1) != um[x].end() )
                    ++t;
                auto fx = um.find(x+1);
                if( fx != um.end() ) {
                    if( fx->second.find(y) != fx->second.end() )
                        ++t;
                     if( fx->second.find(y+1) != fx->second.end() )
                        ++t;
                }
                ++ans[t];
                --ans[0];
            }

            // [x,y] could also be the bottom-left corner of a block
            if( x > 0 && y < n-1 ) {
                long key = ((x-1)<<17) + y;
                auto p = processed.insert(key);
                if( p.second ) {
                    long long t = 1LL;
                    auto fx = um.find(x-1);
                    if( fx != um.end() && fx->second.find(y+1) != fx->second.end() )
                        ++t;
                    if( um[x].find(y+1) != um[x].end() )
                        ++t;
                    ++ans[t];
                    --ans[0];
                }
            }

            // [x,y] could also be the bottom-right corner of a block
            if( x > 0 && y > 0 ) {
                long key = ((x-1)<<17) + (y-1);
                auto p = processed.insert(key);
                if( p.second ) {
                    long long t = 1LL;
                    auto fx = um.find(x-1);
                    if( fx != um.end() && fx->second.find(y) != fx->second.end() )
                        ++t;
                    if( um[x].find(y-1) != um[x].end() )
                        ++t;
                    ++ans[t];
                    --ans[0];
                }
            }

            // [x,y] could also be the top-right corner of a block
            if( x < m-1 && y > 0 ) {
                long key = ((x)<<17) + (y-1);
                auto p = processed.insert(key);
                if( p.second ) {
                    long long t = 1LL;
                    auto fx = um.find(x+1);
                    if( fx != um.end() ) {
                        if( fx->second.find(y) != fx->second.end() )
                            ++t;
                        if( fx->second.find(y-1) != fx->second.end() )
                            ++t;
                    }
                    ++ans[t];
                    --ans[0];
                }
            }
        }

        return ans;
    }
};
