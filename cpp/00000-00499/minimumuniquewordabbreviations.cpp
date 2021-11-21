
// 411. Minimum Unique Word Abbreviation
// https://leetcode.com/problems/minimum-unique-word-abbreviation/





class Solution {
private:
    // adapted from solution to problem 320. Generalized Abbreviation
    // https://leetcode.com/problems/generalized-abbreviation/
    vector<pair<string,int>> generateAbbreviations(string word, int n) {
        // 1 <= word.length <= 21

        // we will use a bitmask to indicate replaced letters
        // 0 indicates letter, 1 indicates replaced

        // skips where a char is replaced with a 1
        // also skips returning the length of word as an abbreviation

        vector<pair<string,int>> ans;
        string t = "";
        int cnt,prev,len;
        bool skip;
        for(int i = 0; i <= pow(2,n)-2; ++i) {

            t.clear();
            len = 0;
            cnt = 0;
            prev = 0;
            skip = false;
            for(int j = n-1; j >= 0; --j) {
                if( i & (1 << j) ) {
                    ++cnt;
                    prev = 1;
                } else {
                    if( prev == 1 ) {
                        if( cnt == 1 ) {
                            skip = true;
                            break;
                        }
                        t += to_string(cnt);
                        ++len;
                        cnt  = 0;
                        prev = 0;
                    }
                    t.push_back(word[n-1-j]);
                    ++len;
                }
            }
            if( !skip ) {
                if( prev == 1 ) {
                    if( cnt == 1 )
                        skip = true;
                    else {
                        t += to_string(cnt);
                        ++len;
                    }
                }
                if( !skip )
                    ans.push_back({t,len});
            }
        }

        return ans;
    }


public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        int m = target.size();

        // words in dictionay with length different than target can be ruled out
        vector<string> dic;
        for(int i = 0; i < dictionary.size(); ++i)
            if( dictionary[i].size() == m )
                dic.push_back(dictionary[i]);
        int n = dic.size();
        if( n == 0 )
            return to_string(m);


        // generate all abbreveations of target and sort them by length
        vector<pair<string,int>> v = generateAbbreviations(target,m);
        sort(v.begin(),v.end(),[](const pair<string,int>& a, const pair<string,int>& b){
           return a.second < b.second;
        });

        /*
        for(int i = 0; i < v.size(); ++i)
            cout << v[i].first << " ";
        cout << endl;
        */


        // starting with the smallest abbreviation of target
        // determine if any word in dictionary has the same abbreviation

        string abbr,word,t;
        int asz,p;
        bool flag;
        vector<pair<char,int>> ci;

        for(int i = 0; i < v.size(); ++i) {         // abbreviations
            abbr = v[i].first;
            asz = abbr.size();

            ci.clear();
            t = "";
            p = 0;
            for(int j = 0; j < asz; ++j) {
                if( isdigit(abbr[j]) ) {
                    t += abbr[j];
                    continue;
                }
                if( !t.empty() ) {
                    p += stoi(t);
                    t = "";
                }
                ci.push_back({target[p],p});
                ++p;
            }

            /*
            cout << "abbreviation " << abbr << endl;
            for(auto it = ci.begin(); it != ci.end(); ++it)
                cout << (*it).first << ":" << (*it).second << " ";
            cout << endl;
            */



            flag = false; // assume we don't have a match
            for(int j = 0; j < dic.size(); ++j) {   // words in dic
                word = dic[j];

                flag = true;
                for(auto it = ci.begin(); it != ci.end(); ++it) {
                    // cout << (*it).first << ":" << (*it).second << " ";
                    if( (*it).first != word[(*it).second] ) {
                        flag = false;
                        break;
                    }
                }
                if( flag ) // move on to next shortest abbreviation
                    break;
            }

            if( !flag )
                return abbr;

        }

        // satisfy compiler
        return target;
    }
};
