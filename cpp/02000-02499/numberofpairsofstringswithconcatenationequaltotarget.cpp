
// 2023. Number of Pairs of Strings With Concatenation Equal to Target
// https://leetcode.com/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/





class Solution {
private:
    bool starts_with(string& s, string& start) {
        for(int i = 0; i < start.size(); ++i)
            if( s[i] != start[i] )
                return false;
        return true;
    }

    bool ends_with(string& s, string& end) {
        int offset = s.size() - end.size();
        for(int i = 0; i < end.size(); ++i)
            if( s[offset+i] != end[i] )
                return false;
        return true;
    }

public:
    int numOfPairs(vector<string>& nums, string target) {
        int tsz = target.size();
        int n = nums.size();

        unordered_map<int,vector<int>> um;
        pair<unordered_map<int,vector<int>>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = um.insert({nums[i].size(),{i}});
            if( !p.second )
                p.first->second.push_back(i);
        }


        int ans = 0;
        int j;
        int seen[n][n];memset(seen,0,sizeof seen);
        for(int i = 0; i < n; ++i) {
            if( nums[i].size() >= tsz )
                continue;


            // would there even be any other strings nums[j], so that
            // tsz = nums[i].size() + nums[j].size()
            int l = tsz - nums[i].size();
            auto f = um.find(l);
            if( f == um.end() )
                continue;
            if( l == nums[i].size() && f->second.size() == 1 )
                continue;


            // does target start with nums[i]?
            if( starts_with(target,nums[i]) ) {
                for(int k = 0; k < f->second.size(); ++k) {
                    j = f->second[k];
                    if( j == i )
                        continue;
                    if( !seen[i][j] && ends_with(target,nums[j]) ) {
                        ++ans;
                        seen[i][j] = 1;
                    }
                }
            }

            // does target end with nums[i]?
            if( ends_with(target,nums[i]) ) {
                for(int k = 0; k < f->second.size(); ++k) {
                    j = f->second[k];
                    if( j == i )
                        continue;
                    if( !seen[j][i] && starts_with(target,nums[j]) ) {
                        ++ans;
                        seen[j][i] = 1;
                    }
                }
            }

        }

        return ans;
    }
};
