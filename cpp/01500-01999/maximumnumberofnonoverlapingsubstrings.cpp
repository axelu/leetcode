
// 1520. Maximum Number of Non-Overlapping Substrings
// https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/


class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        // for each char record first and last occurence
        vector<vector<int>> by_char(26,vector<int>(2,-1));
        for(int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if( by_char[c][0] == -1 )
                by_char[c][0] = i;
            by_char[c][1] = i;
        }

        map<int,char> by_begin; // first occurence of char
        map<int,char> by_end;   // last occurence of char
        for(int i = 0; i < 26; ++i) {
            if( by_char[i][0] != -1 ) {
                by_begin[by_char[i][0]] = 'a' + i;
                by_end[by_char[i][1]] = 'a' + i;
            }
        }

        unordered_map<int,int> substrings;  // begin,end
        for(int i = 0; i < 26; ++i) {       // for each char
            int curr_begin = by_char[i][0];
            if( curr_begin == -1 )
                continue;
            int curr_end = by_char[i][1];
            if( curr_begin + 1 == curr_end ) {
                substrings[curr_begin] = curr_end;
                continue;
            }

            for(int j = curr_begin+1; j < curr_end; ++j) {
                int e = by_char[s[j]-'a'][1];
                curr_end = max(curr_end,e);

                int b = by_char[s[j]-'a'][0];
                if( b < curr_begin ) {
                    curr_begin = b;
                    j = b;
                }
            }
            substrings[curr_begin] = curr_end;

        }
        // for(auto p: substrings)
        //   cout << p.first << ":" << p.second << " " << s.substr(p.first, p.second - p.first + 1) << endl;

        vector<vector<int>> intervals;
        for(auto p: substrings)
            intervals.push_back({p.first,p.second});
        // sort intervals aka substrings by size asc
        sort(intervals.begin(),intervals.end(),[](const vector<int>& a, const vector<int>& b){
            int a_sz = a[1] - a[0] + 1;
            int b_sz = b[1] - b[0] + 1;
            if( a_sz < b_sz ) {
                return true;
            } else if( a_sz == b_sz ) {
                if( a[0] < b[0] ) {
                    return true;
                }
            }
            return false;
        });

        map<int,int> take;
        for(auto v: intervals) {
            int b = v[0];
            int e = v[1];
            if( take.empty() ) {
                take.insert({b,e});
                continue;
            }

            auto ub = take.upper_bound(b);
            if( ub == take.end() ) {
                // check if we overlap with last interval
                if( take.rbegin()->second < b )
                    take.insert({b,e});
            } else {
                // check if we overlap with next interval OR
                // with prior interval
                if( e > ub->first )
                    continue;
                if( ub != take.begin() ) {
                    if( b < prev(ub)->second )
                        continue;
                }
                take.insert({b,e});
            }
        }

        vector<string> ans;
        for(auto p: take) {
            // cout << p.first << ":" << p.second << " " << s.substr(p.first, p.second - p.first + 1) << endl;
            ans.push_back(s.substr(p.first, p.second - p.first + 1));
        }

        return ans;
    }
};
