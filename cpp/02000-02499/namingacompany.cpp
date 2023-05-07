
// 2306. Naming a Company
// https://leetcode.com/problems/naming-a-company/





/*
 * example
 * ["aabc","babc","cabc","fabc","adef","bdef","cdef","ddef","gdef"]
 * group by 'suffix': all but first letter and then set which 1st letters we have
 * suffix   a b c d e f g h i j k l m n o p q r s t u v w x y z
 * abc      x x x     x
 * def      x x x x     x
 * so we can make number of letters in 1st suffix that we don't have in 2nd suffix *
 *                number of letters in 2nd suffix that we don't have in 1st suffix
 * as we can reverse the order of the strings, we take that number time 2

 */
class Solution {
public:
    long long distinctNames(vector<string>& ideas) {
        // All the strings in ideas are unique.

        unordered_set<string> um[26];

        for(string& s: ideas) {
            char one = s[0];
            s.erase(0,1);
            um[one-'a'].insert(s);
        }

        long long ans = 0;

        for(int i = 0; i < 25; ++i) {
            auto& suffixes_i = um[i];

            for(int j = i+1; j < 26; ++j) {
                auto& suffixes_j = um[j];

                int common_suffixes_cnt = 0;
                for(auto& s: suffixes_i) {
                    if( suffixes_j.find(s) != suffixes_j.end() )
                        ++common_suffixes_cnt;
                }
                long long s1 = suffixes_i.size() - common_suffixes_cnt;
                long long s2 = suffixes_j.size() - common_suffixes_cnt;
                ans += (s1 * s2) * 2;
            }
        }

        return ans;
    }
};

// TLE
/*
class Solution {
public:
    long long distinctNames(vector<string>& ideas) {
        // All the strings in ideas are unique.
        unordered_map<string,int> um;

        for(string& s: ideas) {
            char one = s[0];
            s.erase(0,1);

            auto p = um.insert({s,0});
            p.first->second |= 1<<(one-'a');
        }


        //for(auto it = um.begin(); it != um.end(); ++it) {
        //    cout << it->first << " ";
        //    for(int i = 0; i < 26; ++i)
        //        cout << char('a'+i) << ":" << ((it->second >> i) & 1) << " ";
        //   cout << endl;
        //}


        long long ans = 0;

        for(auto ito = um.begin(); ito != um.end(); ++ito) {
            // cout << "ito->first " << ito->first << endl;

            for(auto iti = next(ito); iti != um.end(); ++iti) {
                // cout << "    iti->first " << iti->first << endl;

                long long s1 = 0LL; // number of letters in 1st suffix that we don't have in 2nd suffix
                long long s2 = 0LL; // number of letters in 2nd suffix that we don't have in 1st suffix
                for(int i = 0; i < 26; ++i) {
                    bool b1 = (ito->second >> i) & 1;
                    bool b2 = (iti->second >> i) & 1;
                    if( b1 && !b2 )
                        ++s1;
                    else if( !b1 && b2 )
                        ++s2;
                }
                ans += (s1 * s2) * 2;
            }
        }

        return ans;
    }
};
*/
