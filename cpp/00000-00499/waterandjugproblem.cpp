
// 365. Water and Jug Problem
// https://leetcode.com/problems/water-and-jug-problem/
// The famous Die Hard example https://www.youtube.com/watch?v=BVtQNK_ZUJg&ab_channel=notnek01
// Input: jug1Capacity = 3, jug2Capacity = 5, targetCapacity = 4
// Output: true
// another example case 23/28
// Input: jug1Capacity = 104707, jug2Capacity = 104711, targetCapacity = 1
// Output: true

// attempt 1
// passes all 28 test cases, but still TLE as it took to long to pass all test cases
/*
class Solution {
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        unordered_set<long> seen;

        // BFS
        queue<array<int,2>> q;
        q.push({0,0});
        seen.insert(0);

        int jug1,jug2,jug1_new,jug2_new,d;
        long state;
        while( !q.empty() ) {
            jug1 = q.front()[0];
            jug2 = q.front()[1];
            q.pop();

            if( jug1 == targetCapacity || jug2 == targetCapacity || jug1 + jug2 == targetCapacity )
                return true;

            // Fill jug1 with water
            if( jug1 < jug1Capacity ) {
                state = (long)jug1Capacity << 20;
                state += jug2;
                if( !seen.count(state) ) {
                    seen.insert(state);
                    q.push({jug1Capacity,jug2});
                }
            }

            // Fill jug2 with water
            if( jug2 < jug2Capacity ) {
                state = (long)jug1 << 20;
                state += jug2Capacity;
                if( !seen.count(state) ) {
                    seen.insert(state);
                    q.push({jug1,jug2Capacity});
                }
            }

            // Empty jug1
            if( jug1 > 0 ) {
                if( !seen.count(jug2) ) {
                    seen.insert(jug2);
                    q.push({0,jug2});
                }
            }

            // Empty jug2
            if( jug2 > 0 ) {
                state = (long)jug1 << 20;
                if( !seen.count(state) ) {
                    seen.insert(state);
                    q.push({jug1,0});
                }
            }

            // Pour water from jug1 into jug2 till either
            //     jug2 is completely full, or jug1 itself is empty
            if( jug1 > 0 && jug2 < jug2Capacity ) {
                d = min(jug1,jug2Capacity-jug2);
                jug1_new = jug1 - d;
                jug2_new = jug2 + d;
                state = (long)jug1_new << 20;
                state += jug2_new;
                if( !seen.count(state) ) {
                    seen.insert(state);
                    q.push({jug1_new,jug2_new});
                }
            }

            // Pour water from jug2 into jug1 till either
            //     jug1 is completely full, or jug2 itself is empty
            if( jug1 < jug1Capacity && jug2 > 0 ) {
                d = min(jug1Capacity-jug1,jug2);
                jug1_new = jug1 + d;
                jug2_new = jug2 - d;
                state = (long)jug1_new << 20;
                state += jug2_new;
                if( !seen.count(state) ) {
                    seen.insert(state);
                    q.push({jug1_new,jug2_new});
                }
            }
        }

        return false;
    }
};
*/

class Solution {
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        // 1 <= jug1Capacity, jug2Capacity, targetCapacity <= 10^6

        // at no point can jug1+jug2 be greater than jug1Capacity+jug2Capacity
        int totalCapacity = jug1Capacity + jug2Capacity;

        // also, because of 1 <= jug1Capacity, jug2Capacity, targetCapacity -> jug1+jug2 > 0
        // so we can only see valid states [1,jug1Capacity+jug2Capacity] inclusive

        int seen[totalCapacity+1];memset(seen,0,sizeof seen);

        // BFS
        queue<int> q;
        q.push(0);
        seen[0] = 1;

        int total_new;
        while( !q.empty() ) {
            int total = q.front();
            q.pop();

            if( total == targetCapacity )
                return true;

            // empty jug 1
            total_new = total - jug1Capacity;
            if( total_new >= 1 && !seen[total_new] ) {
                seen[total_new] = 1;
                q.push(total_new);
            }
            // empty jug 2
            total_new = total - jug2Capacity;
            if( total_new >= 1 && !seen[total_new] ) {
                seen[total_new] = 1;
                q.push(total_new);
            }
            // pour jug1 into jug2 of fill jug1
            total_new = total + jug1Capacity;
            if( total_new <= totalCapacity && !seen[total_new] ) {
                seen[total_new] = 1;
                q.push(total_new);
            }
            // pour jug2 into jug1 or fill jug2
            total_new = total + jug2Capacity;
            if( total_new <= totalCapacity && !seen[total_new] ) {
                seen[total_new] = 1;
                q.push(total_new);
            }
        }

        return false;
    }
};
