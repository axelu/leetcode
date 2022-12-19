
// 2383. Minimum Hours of Training to Win a Competition
// https://leetcode.com/problems/minimum-hours-of-training-to-win-a-competition/


class Solution {
public:
    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int>& energy, vector<int>& experience) {
        int n = energy.size(); // energy.size() == experience.size()

        int t = 0;

        int egy = initialEnergy;
        int exp = initialExperience;
        for(int i = 0; i < n; ++i) {

            // both, our energy AND or experience must be strictly greater than
            // that of our oponents
            if( egy > energy[i] && exp > experience[i] ) {
                // we can defeat our current opponent
            } else if( egy > energy[i] && exp <= experience[i] ) {
                t += experience[i] - exp + 1;
                exp += experience[i] - exp + 1;
            } else if( egy <= energy[i] && exp > experience[i] ) {
                t += energy[i] - egy + 1;
                egy += energy[i] - egy + 1;
            } else { // egy <= energy[i] && exp <= experience[i]
                t += experience[i] - exp + 1;
                exp += experience[i] - exp + 1;
                t += energy[i] - egy + 1;
                egy += energy[i] - egy + 1;
            }
            egy -= energy[i];
            exp += experience[i];
        }

        return t;
    }
};
