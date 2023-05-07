
// 2491. Divide Players Into Teams of Equal Skill
// https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/




class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int n = skill.size(); // n is even

        sort(skill.begin(),skill.end());

        // first pair
        int total_skill = skill[0] + skill[n-1];

        long long ans = skill[0] * skill[n-1];

        int i = 1;
        int j = n-2;
        while( i < j ) {
            if( skill[i] + skill[j] != total_skill )
                return -1LL;
            ans = ans + (skill[i] * skill[j]);
            ++i;
            --j;
        }

        return ans;
    }
};
