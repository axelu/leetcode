
// 1792. Maximum Average Pass Ratio
// https://leetcode.com/problems/maximum-average-pass-ratio/




class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size();

        // we want to add the extraStudents to the class where
        // adding them makes the biggest difference (greedy)

        auto cmp = [](vector<vector<int>>::iterator a, vector<vector<int>>::iterator b){
            double apr_org = (double)(*a)[0]/(*a)[1];
            double apr_new = (double)((*a)[0]+1)/((*a)[1]+1);
            double apr_dif = apr_new - apr_org;

            double bpr_org = (double)(*b)[0]/(*b)[1];
            double bpr_new = (double)((*b)[0]+1)/((*b)[1]+1);
            double bpr_dif = bpr_new - bpr_org;

            return bpr_dif > apr_dif;
        };
        priority_queue<vector<vector<int>>::iterator,vector<vector<vector<int>>::iterator>,decltype(cmp)> pq(cmp);
        for(auto it = classes.begin(); it != classes.end(); ++it)
            pq.push(it);

        while( extraStudents > 0 ) {
            auto clss = pq.top();
            pq.pop();

            (*clss)[0] += 1;
            (*clss)[1] += 1;
            --extraStudents;

            pq.push(clss);
        }

        double sum_passratio = 0.0;
        while( !pq.empty() ) {
            auto clss = pq.top();
            pq.pop();

            double pr = (double)(*clss)[0]/(*clss)[1];
            sum_passratio += pr;
        }

        return sum_passratio/n;
    }
};
