
// 288. Unique Word Abbreviation
// https://leetcode.com/problems/unique-word-abbreviation/





class ValidWordAbbr {
private:
    unordered_map<string,unordered_set<string>> mp;

    string abbreviate(string& s) {
        int n = s.size();
        if( n <= 2 )
            return s;
        else
            return s[0]+to_string(n-2)+s[n-1];
    }

public:
    ValidWordAbbr(vector<string>& dictionary) {
        pair<unordered_map<string,unordered_set<string>>::iterator,bool> p;
        for(int i = 0; i < dictionary.size(); ++i) {
            p = mp.insert({abbreviate(dictionary[i]),{dictionary[i]}});
            if( !p.second )
                p.first->second.insert(dictionary[i]);
        }
        // debug
        /*
        for(auto ito = mp.begin(); ito != mp.end(); ++ito) {
            cout << ito->first << ": ";
            for(auto iti = ito->second.begin(); iti != ito->second.end(); ++iti)
                cout << *iti << " ";
            cout << endl;
        }
        */

    }

    bool isUnique(string word) {
        auto f1 = mp.find(abbreviate(word));
        if( f1 == mp.end() ) {
            return true;
        } else {
            if( f1->second.size() == 1 && f1->second.find(word) != f1->second.end() )
                return true;
        }
        return false;
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
