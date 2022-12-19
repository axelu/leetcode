
-- 2026. Low-Quality Problems
-- https://leetcode.com/problems/low-quality-problems/




/* Write your T-SQL query statement below */


select problem_id
from problems
where cast(likes as float)/(likes+dislikes)*100 < 60
order by problem_id
