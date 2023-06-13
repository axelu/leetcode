
-- 2688. Find Active Users
-- https://leetcode.com/problems/find-active-users/




/* Write your T-SQL query statement below */

with active_users as
(
select
  user_id,
  created_at,
  case
    when lag(created_at,1) over(partition by user_id order by created_at) is null
    then 0
    else
      case
        when datediff(day,lag(created_at,1) over(partition by user_id order by created_at),created_at) <= 7
        then 1
        else 0
      end
  end as active
from
  users
)
select distinct
  user_id
from
  active_users
where
  active = 1
