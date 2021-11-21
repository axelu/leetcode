
// 1737. Change Minimum Characters to Satisfy One of Three Conditions
// https://leetcode.com/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/





class Solution {
private:
    void pre(string& s, int n, map<char,int>& m, int cnt[]) {
        pair<map<char,int>::iterator,bool> p;
        char ch;
        for(int i = 0; i < n; ++i) {
            ch = s[i];
            ++cnt[ch-'a'];
            p = m.insert({ch,1});
            if( !p.second )
                ++p.first->second;
        }
    }

    int mem[26][26];

    int rec(map<char,int>& ma, int posa, map<char,int>& mb, int posb) {
        // goal: current char in a greater than current char in b
        // cout << "posa " << posa << " posb " << posb << endl;

        auto ita = ma.begin(); advance(ita,posa);
        char cha = ita->first;
        int cnta = ita->second;
        int na   = ma.size();
        auto itb = mb.begin();advance(itb,posb);
        char chb = itb->first;
        int cntb = itb->second;

        if( cha > chb ) {
            return 0;
        }

        if( posa == na-1 && posb == 0 ) {
            // the only option is that cha == chb
            // in this case we would have converted all letters in a and b to
            // cha respectively chb at this point
            return 0;
        }


        if( mem[posa][posb] != -1 )
            return mem[posa][posb];


        int reta = INT_MAX;
        if( posa < na-1 )
            reta = cnta + rec(ma,posa+1,mb,posb);
        else {
            // if the largest letter in a is not a 'z',
            // then we can advance in a to 'y'
            reta = cnta;
            if( prev(mb.end())->first == 'z' )
                reta += prev(mb.end())->second;
        }

        int retb;
        if( posb > 0 )
            retb = cntb + rec(ma,posa,mb,posb-1);
        else {
            // if the smallest letter in b is not an 'a',
            // then we can advance in b to 'b'
            retb = cntb;
            if( ma.begin()->first == 'a' )
                retb += ma.begin()->second;
        }


        return mem[posa][posb] = min(reta,retb);
        // return min(reta,retb);
    }

public:
    int minCharacters(string& a, string& b) {
        int na = a.size();
        int nb = b.size();

        map<char,int> ma;
        int cnta[26];memset(cnta,0,sizeof cnta);

        map<char,int> mb;
        int cntb[26];memset(cntb,0,sizeof cntb);


        pre(a,na,ma,cnta);
        pre(b,nb,mb,cntb);

        // if either all chars in a and b are already the same OR
        // there is only one char in a and one char in b
        if( ma.size() == 1 && mb.size() == 1 )
            return 0;

        // if the largest char in a is less than the smallest char in b
        // or vice versa
        if( prev(ma.end())->first < mb.begin()->first ||
            prev(mb.end())->first < ma.begin()->first )
            return 0;


        // condition #3: both a and b consist of only one distinct letter
        // we are looking for the char with the most occurences
        int ml = 0;
        for(int i = 0; i < 26; ++i)
            ml = max(ml,cnta[i]+cntb[i]);
        int ans3 = na+nb-ml;
        // cout << "ans3 " << ans3 << endl;


        // condition #2: every letter in b is strictly less than every letter in a
        memset(mem,-1,sizeof mem);
        int ans2 = rec(ma,0,mb,mb.size()-1);
        // cout << "ans2 " << ans2 << endl;

        // condition #1: every letter in a is strictly less than every letter in b
        memset(mem,-1,sizeof mem);
        int ans1 = rec(mb,0,ma,ma.size()-1);
        // cout << "ans1 " << ans1 << endl;

        return min({ans1,ans2,ans3});
    }
};
