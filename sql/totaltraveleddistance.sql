
-- 2837. Total Traveled Distance
-- https://leetcode.com/problems/total-traveled-distance/





/* Write your T-SQL query statement below */


select
    u.user_id,
    u.name,
    sum(isnull(r.distance, 0)) as [traveled distance]
from
    Users as u left outer join Rides as r on u.user_id = r.user_id
group by
    u.user_id, u.name
order by
    u.user_id
