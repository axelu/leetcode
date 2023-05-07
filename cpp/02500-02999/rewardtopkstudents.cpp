
// 2512. Reward Top K Students
// https://leetcode.com/problems/reward-top-k-students/



class Solution {
public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {

        unordered_set<string> dic_positive;
        for(string& s: positive_feedback)
            dic_positive.insert(s);

        unordered_set<string> dic_negative;
        for(string& s: negative_feedback)
            dic_negative.insert(s);

        unordered_map<int,int> scores; // student_id, score

        int n = report.size(); // report.length == student_id.length
        for(int i = 0; i < n; ++i) {
            int t = 0;
            stringstream ss(report[i]);
            string s;
            while( getline(ss,s,' ') ) {
                if( dic_positive.find(s) != dic_positive.end() )
                    t += 3;
                else if( dic_negative.find(s) != dic_negative.end() )
                    --t;
            }
            scores[student_id[i]] += t;
        }

        vector<pair<int,int>> v;
        for(auto p: scores)
            v.push_back(p);
        sort(v.begin(),v.end(),[](const pair<int,int>& a, const pair<int,int>& b){
            if( a.second > b.second ) {
                return true;
            } else if( a.second == b.second ) {
                if( a.first < b.first ) {
                    return true;
                }
            }
            return false;
        });

        vector<int> ans;
        for(int i = 0; i < min(k,(int)v.size()); ++i)
            ans.push_back(v[i].first);

        return ans;
    }
};
