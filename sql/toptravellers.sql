
-- 1407. Top Travellers
-- https://leetcode.com/problems/top-travellers/

/* Write your T-SQL query statement below */


select
  u.name as name,
  0 as travelled_distance
from
  users as u
where u.id not in (
    select user_id from rides
  )

union

select
  u.name,
  t.dist
from (
    select
      user_id,
      sum(distance) as dist
    from
      rides
    group by user_id
  ) as t inner join users u on t.user_id = u.id

order by travelled_distance desc
