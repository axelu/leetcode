
-- 3150. Invalid Tweets II
-- https://leetcode.com/problems/invalid-tweets-ii/




/* Write your T-SQL query statement below */

select tweet_id
from Tweets
where
    len(content) > 140 or
    len(content) - len(replace(content,'@','')) > 3 or
    len(content) - len(replace(content,'#','')) > 3
