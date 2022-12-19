
-- 1435. Create a Session Bar Chart
-- https://leetcode.com/problems/create-a-session-bar-chart/



/* Write your T-SQL query statement below */

select '[0-5>' as bin,
       count(*) as total
from sessions
where duration < 300
union
select '[5-10>',
       count(*)
from sessions
where duration >= 300 and duration < 600
union
select '[10-15>',
       count(*)
from sessions
where duration >= 600 and duration < 900
union
select '15 or more',
       count(*)
from sessions
where duration >= 900
