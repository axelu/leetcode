
-- 1667. Fix Names in a Table
-- https://leetcode.com/problems/fix-names-in-a-table/



/* Write your T-SQL query statement below */

select
  u.user_id,
  upper(substring(u.name,1,1)) + lower(substring(u.name,2,len(u.name)-1)) as name
from
  users as u
order by
  user_id
