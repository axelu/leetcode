
-- 1972. First and Last Call On the Same Day
-- https://leetcode.com/problems/first-and-last-call-on-the-same-day/



/* Write your T-SQL query statement below */

with users
as
(
select distinct caller_id as user_id from calls
union
select distinct recipient_id from calls
),

callsplus
as
(
select
  u.user_id,
  case when c.caller_id < c.recipient_id then c.caller_id else c.recipient_id end as user1_id,
  case when c.caller_id > c.recipient_id then c.caller_id else c.recipient_id end as user2_id,
  rank() over(partition by u.user_id,format(c.call_time,'yyyy-MM-dd') order by c.call_time) as first_call,
  rank() over(partition by u.user_id,format(c.call_time,'yyyy-MM-dd') order by c.call_time desc) as last_call
from
  users u join calls c on u.user_id = c.caller_id or u.user_id = c.recipient_id
)

select distinct
  c1.user_id
from
  callsplus c1 join callsplus c2 on
    c1.user_id = c2.user_id and
    c2.last_call = 1 and
    c1.user1_id = c2.user1_id and c1.user2_id = c2.user2_id
where
  c1.first_call = 1

