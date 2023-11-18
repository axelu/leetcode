

// 2933. High-Access Employees
// https://leetcode.com/problems/high-access-employees/




class Solution {
private:
    int twentyfourhour2minofday(string t) {
        string hour_str = t.substr(0,2);
        int hour = stoi(hour_str);

        string min_str = t.substr(2);
        int min = stoi(min_str);

        return hour * 60 + min;
    }

public:
    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
        unordered_map<string,vector<string>> um; // employee name, list of sorted access times

        for(auto& access_time: access_times)
            um[access_time[0]].push_back(access_time[1]);

        vector<string> ans;

        for(auto ito = um.begin(); ito != um.end(); ++ito) {
            // cout << "employee " << ito->first << endl;

            sort(ito->second.begin(),ito->second.end());

            // sliding window per employee
            int i = 0;
            int i_min = twentyfourhour2minofday(ito->second[i]);
            for(int j = 0; j < ito->second.size(); ++j) {
                // cout << ito->second[j] << " " << endl;

                int l = j - i + 1;
                int j_min = twentyfourhour2minofday(ito->second[j]);
                if( l == 3 && j_min - i_min < 60 ) {
                    ans.push_back(ito->first);
                    break;
                }

                while( j_min - i_min >= 60 && i < j ) {
                    ++i;
                    i_min = twentyfourhour2minofday(ito->second[i]);
                }
            }
        }

        return ans;
    }
};
