
-- 602. Friend Requests II: Who Has the Most Friends
-- https://leetcode.com/problems/friend-requests-ii-who-has-the-most-friends/




/* Write your T-SQL query statement below */

with a
as
(
select
  requester_id as id,
  count(*) as cnt
from
  requestaccepted
group by
  requester_id
union all
select
  accepter_id as id,
  count(*) as cnt
from
  requestaccepted
group by
  accepter_id
),
b
as
(
select
 id,
 sum(cnt) as num
from
 a
group by
 id
),
c
as
(
select
  id,
  num,
  rank() over(order by num desc) as rnk
from
  b
)
select id,num from c where rnk = 1
