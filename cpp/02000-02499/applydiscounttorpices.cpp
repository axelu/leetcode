
// 2288. Apply Discount to Prices
// https://leetcode.com/problems/apply-discount-to-prices/




class Solution {
private:
    vector<string> get_words(string& sentence) {
        vector<string> v;
        stringstream ss(sentence);
        string s;
        while( getline(ss,s,' ') ) {
            v.push_back(s);
        }
        return v;
    }

    bool is_price(string& word) {
        int w_sz = word.size();
        if( w_sz == 1 || word[0] != '$' )
            return false;
        for(int i = 1; i < w_sz; ++i)
            if( !isdigit(word[i]) )
               return false;

        return true;
    }

public:
    string discountPrices(string sentence, int discount) {
        vector<string> words = get_words(sentence);
        string ans;
        double dbl_discount = (100.0 - discount)/100.0;
        for(int i = 0; i < words.size(); ++i) {
            if( i > 0 )
                ans += " ";

            if( !is_price(words[i]) ) {
                ans += words[i];
            } else {
                long t = stol(words[i].substr(1));
                double discounted_price = t * dbl_discount;

                stringstream ss;
                ss << fixed << setprecision(2) << discounted_price;
                ans += "$" + ss.str();
            }
        }

        return ans;
    }
};
