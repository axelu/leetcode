
-- 1303. Find the Team Size
-- https://leetcode.com/problems/find-the-team-size/


/* Write your T-SQL query statement below */


WITH userData (team_id, team_size)
AS
(
    select team_id, count(employee_id)
    from employee
    group by team_id
)
select a.employee_id, b.team_size
from employee as a, userData as b
where a.team_id = b.team_id


