
// 3606. Coupon Code Validator
// https://leetcode.com/problems/coupon-code-validator/


class Solution {
private:
    unordered_set<string> validBusinessLines{"electronics", "grocery", "pharmacy", "restaurant"};

    bool isValidCouponCode(string code) {
        if( code.empty() )
            return false;

        for(char c: code)
            if( !isalnum(c) && c != '_' )
                return false;

        return true;
    }

    bool isValidBusinessLine(string businessLine) {
        return validBusinessLines.find(businessLine) != validBusinessLines.end();
    }

public:
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        int n = code.size(); // code.size() == businessLine.size() == isActive.size()

        // return an array of the codes of all valid coupons,
        // sorted first by their businessLine in the order:
        // "electronics", "grocery", "pharmacy", "restaurant"
        // (note: this happens to be their lexicographically order)
        // and then by code in lexicographical (ascending) order within each category.

        vector<vector<string>> t;
        for(int i = 0; i < n; ++i) {
            // cout << code[i] << " " << businessLine[i] << " " << isActive[i] << endl;
            // cout << isValidCouponCode(code[i]) << " " << isValidBusinessLine(businessLine[i]) << endl;

            if( !isActive[i] || !isValidCouponCode(code[i]) || !isValidBusinessLine(businessLine[i]) )
                continue;

            t.push_back({businessLine[i],code[i]});
        }

        sort(t.begin(), t.end());

        vector<string> ans;
        for(int i = 0; i < t.size(); ++i)
            ans.push_back(t[i][1]);

        return ans;
    }
};
