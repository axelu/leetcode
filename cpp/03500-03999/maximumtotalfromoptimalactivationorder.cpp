
// 3645. Maximum Total from Optimal Activation Order
// https://leetcode.com/problems/maximum-total-from-optimal-activation-order/






/*
    Criteria from the problem description:
        (1) To activate an inactive element at index i, the number of currently
            active elements must be strictly less than limit[i].
        (2) When you activate the element at index i, it adds value[i] to the
            total activation value (i.e., the sum of value[i] for all elements
            that have undergone activation operations).
        (3) After each activation, if the number of currently active elements
            becomes x, then all elements j with limit[j] <= x become
            permanently inactive, even if they are already active.

    Criteria 3 was initially unclear. Lets look at 2 of the given examples and
    their give explanation.

    Example 1: value = [3,5,8], limit = [2,1,3] => ans 16

    Step    Activated   value[i]    Active  Active  Becomes Inactive    Inactive Elements   Running
                i                   Before  After          j                                Total
                                      i       i
    ====    =========   ========    ======  ======  ================    =================   =======
      1	        1	        5	      0       1	    j = 1	            [1]	                5
                                                    as limit[1] = 1
    ----    ---------   --------    ------  ------  ----------------    -----------------   -------
      2	        0	        3	      0	      1	    -	                [1]	                8
    ----    ---------   --------    ------  ------  ----------------    -----------------   -------
      3	        2	        8	      1	      2	    j = 0 	            [1, 2]	            16
                                                    as limit[0] = 2

    So why at step 2 is "Active Before i" = 0 ???
    It becomes clear if we add to above table the list of remaining elements and show with ones are already active.

    Step    Activated   value[i]    Active  Active  Becomes Inactive    Inactive Elements   Running     Remaining Elements
                i                   Before  After          j            (index)             Total       (* permantly inactive)
                                      i       i
    ====    =========   ========    ======  ======  ================    =================   =======     ======================
      1	        1	        5	      0       1	    j = 1	            [1]	                5           [3,*,5]
                                                    as limit[1] = 1
    ----    ---------   --------    ------  ------  ----------------    -----------------   -------     ----------------------
      2	        0	        3	      0	      1	    -	                [1]	                8           [3,*,5]
                                                                                                         A
    ----    ---------   --------    ------  ------  ----------------    -----------------   -------     ----------------------
      3	        2	        8	      1	      2	    j = 0 	            [1, 2]	            16
                                                    as limit[0] = 2

    After step 1, we have 1 active element, so we render all indices j with limit[j] <= 1 as permanently inactive.
    After that, in the remaining elements, there are 0 activated indexes, hence at step 2, we start with 0 active elements.
    After step 2, in the remaining elements, there is 1 activated index, but all remaining limits are > 1.
    After that, in the remaining elements, there is 1 activated index, hence at step 3, we start with 1 active element.



    Let us look at example 3: value = [4,1,5,2], limit = [3,3,2,3] => ans 12

    Step    Activated   value[i]    Active  Active  Becomes Inactive    Inactive Elements   Running     Remaining Elements
                i                   Before  After          j            (index)             Total       (* permantly inactive)
                                      i       i
    ====    =========   ========    ======  ======  ================    =================   =======     ======================
      1         2           5         0       1            -            []                  5           [4,1,5,2]
                                                                                                             A
    ----    ---------   --------    ------  ------  ----------------    -----------------   -------     ----------------------
      2         0           4         1       2     j = 2               [2]                 9           [4,1,*,2]
                                                    limit[2] = 2                                         A
    ----    ---------   --------    ------  ------  ----------------    -----------------   -------     ----------------------
      3         1           1         1       2            -            [2]                 10          [4,1,*,2]
                                                                                                         A A
    ----    ---------   --------    ------  ------  ----------------    -----------------   -------     ----------------------
      4         3           2         2       3     j = 0, 1, 3 as      [0,1,2,3]           12          [*,*,*,*]
                                                    limit[j] = 3

    So why from step 2 to step 3 does X remain 1?
    Because after step 2 we have 2 activated elements, then we run through all limits and mark all where
    limit[j] <= 2 as permanently inactive. After doing so, only 1 activated index remains, hence step 3 starts with 1 active.


    What if we group values by limit?
    Example 3
    limit   2   3
    values  5   4,2,1
    we can then go left to right and keep the 'limit' max values.

    Example
    limit   1       2           4
    value   9,7,4   10,9,8      5,12
    value   8,7,4   20,20,20    5,12



 */
class Solution {
public:
    long long maxTotal(vector<int>& value, vector<int>& limit) {
        int n = value.size(); // value.size() == limit.size()

        map<int,multiset<int>> mp;
        for(int i = 0; i < n; ++i) {
            mp[limit[i]].insert(value[i]);
        }

        long long ans = 0LL;
        for(auto ito = mp.begin(); ito != mp.end(); ++ito) {
            int i = 0;
            for(auto iti = ito->second.rbegin(); i < ito->first && iti != ito->second.rend(); ++iti) {
                ans += (long long)(*iti);
                ++i;
            }
        }

        return ans;
    }
};
