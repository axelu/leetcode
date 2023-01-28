
-- 262. Trips and Users
-- https://leetcode.com/problems/trips-and-users/



/* Write your T-SQL query statement below */
with cte
as
(
select
  t.id,
  t.client_id,
  c.banned as client_banned,
  t.driver_id,
  d.banned as driver_banned,
  t.status,
  t.request_at
from
  trips t left join users c on t.client_id = c.users_id and c.role = 'client'
          left join users d on t.driver_id = d.users_id and d.role = 'driver'
where
  c.banned = 'No' and
  d.banned = 'No' and
  t.request_at between '2013-10-01' and '2013-10-03'
),
total_req_per_day
as
(
select
  cte.request_at as Day,
  count(*) as cnt
from
  cte
group by
  cte.request_at
),
canceled_req_per_day
as
(
select
  cte.request_at as Day,
  count(*) as cnt
from
  cte
where
  cte.status <> 'completed'
group by
  cte.request_at
)
select
  t.Day,
  round(cast(isnull(c.cnt,0) as decimal)/t.cnt,2) as [Cancellation Rate]
from
  total_req_per_day t left join canceled_req_per_day c on t.Day = c.Day
