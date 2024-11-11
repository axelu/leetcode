
// 3273. Minimum Amount of Damage Dealt to Bob
// https://leetcode.com/problems/minimum-amount-of-damage-dealt-to-bob/





class Solution {
public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        int n = damage.size(); // damage.size() == health.size()

        auto cmp = [power](const vector<int>& a, const vector<int>& b){
            unsigned long long damage_a = a[0];
            unsigned long long health_a = a[1];

            unsigned long long fa = health_a / power;
            if( health_a % power )
                ++fa;
            // it will take fa rounds to get rid of enemy a


            unsigned long long damage_b = b[0];
            unsigned long long health_b = b[1];

            unsigned long long fb = health_b / power;
            if( health_b % power )
                ++fb;
            // it will take fb rounds to get rid of enemy b

            // points we rack up if we elminate a first
            unsigned long long pa = (fa * (damage_a + damage_b)) + (fb * damage_b);

            // points we rack up if we elminate ab first
            unsigned long long pb = (fb * (damage_a + damage_b)) + (fa * damage_a);

            return pa > pb;
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

        long long damageperround = 0LL;
        for(int i = 0; i < n; ++i) {
            pq.push({damage[i], health[i]});
            damageperround += damage[i];
        }

        long long ans = 0LL;

        while( !pq.empty() ) {
            long long _damage = pq.top()[0];
            int _health = pq.top()[1];
            pq.pop();

            long long f = _health / power;
            if( _health % power )
                ++f;

            ans += f * damageperround;
            damageperround -= _damage;
        }

        return ans;
    }
};
