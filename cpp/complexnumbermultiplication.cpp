
// 537. Complex Number Multiplication
// https://leetcode.com/problems/complex-number-multiplication/


class Solution {
private:
    pair<int,int> getRealAndImaginaryParts(string s) {
        int n = s.size();
        int p = s.find('+');
        int x = stoi(s.substr(0,p+1));
        int y = stoi(s.substr(p+1,n-1-(p+1)));
        return make_pair(x,y);
    }

public:
    string complexNumberMultiply(string z, string w) {
        // https://en.wikipedia.org/wiki/Complex_number
        // z = x + yi and w = u + vi
        // z * w = (xu-yv)+(xv+yu)i by the distributive law

        auto[x,y] = getRealAndImaginaryParts(z);
        auto[u,v] = getRealAndImaginaryParts(w);

        string ans = to_string(x*u-y*v) + "+" + to_string(x*v+y*u) + "i";
        return ans;
    }
};
