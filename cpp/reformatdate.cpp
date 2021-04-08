
// Reformat Date
// https://leetcode.com/problems/reformat-date/


class Solution {
public:
    string reformatDate(string date) {

        int s = date.size();

        string y = date.substr(s-4);
        string m = months.find(date.substr(s-8,3))->second;

        // regex re_d("[0-9]");
        // string d = ( regex_match(date.substr(1,1),re_d) ) ? date.substr(0,2) : "0" + date.substr(0,1);
        string d = ( isdigit(date[1])) ? date.substr(0,2) : "0" + date.substr(0,1);

        return y + "-" + m + "-" + d;

    }
private:
    unordered_map<string, string> months {
        { "Jan", "01" },
        { "Feb", "02" },
        { "Mar", "03" },
        { "Apr", "04" },
        { "May", "05" },
        { "Jun", "06" },
        { "Jul", "07" },
        { "Aug", "08" },
        { "Sep", "09" },
        { "Oct", "10" },
        { "Nov", "11" },
        { "Dec", "12" }
    };
};
