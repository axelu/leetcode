
-- 1939. Users That Actively Request Confirmation Messages
-- https://leetcode.com/problems/users-that-actively-request-confirmation-messages/



/* Write your T-SQL query statement below */

select
  distinct f.user_id
from
(

select
  t.user_id,
  t.time_stamp,
  t.prev,
  case
    when t.prev is not null then datediff(second,t.prev,t.time_stamp) else 86402
  end as time_diff
from (
    select
      c.user_id,
      c.time_stamp,
      lag(c.time_stamp,1) over(partition by c.user_id order by c.time_stamp) as prev
    from
      confirmations as c
  ) as t

) as f

where f.time_diff <= 86400
