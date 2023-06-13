
// 1487. Making File Names Unique
// https://leetcode.com/problems/making-file-names-unique/




class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        int n = names.size();

        unordered_map<string,int> um;

        for(auto it = names.begin(); it != names.end(); ++it) {
            // search by 'full name'
            auto f = um.find(*it);

            if( f != um.end() ) {
                // cout << *it << " already taken" << endl;
                // the name is already taken
                // we have no other choice then assining the next smallest k
                int k_candidate = f->second;
                string t = *it + "(" + to_string(k_candidate) + ")";
                while( um.find(t) != um.end() ) {
                    ++k_candidate;
                    t = *it + "(" + to_string(k_candidate) + ")";
                }

                *it = t;
                um.insert({t,1});
                f->second = k_candidate + 1;

            } else {
                // cout << *it << " not seen before" << endl;
                um.insert({*it,1});
            }
        }

        return names;
    }
};
