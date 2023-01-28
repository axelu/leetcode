
-- 1127. User Purchase Platform
-- https://leetcode.com/problems/user-purchase-platform/




/* Write your T-SQL query statement below */

with spendingplatform
as
(
select *
from
(
  select user_id, spend_date, platform, amount from spending
) as SourceTable
pivot (sum(amount) for platform in (desktop,mobile)) as PivotTable
),

mobileonly
as
(
select
  spend_date,
  sum(mobile) as total_amount,
  count(distinct user_id) as total_users
from
  spendingplatform
where
  desktop is null
group by
  spend_date
),

desktoponly
as
(
select
  spend_date,
  sum(desktop) as total_amount,
  count(distinct user_id) as total_users
from
  spendingplatform
where
  mobile is null
group by
  spend_date
),

both
as
(
select
  spend_date,
  sum(desktop) +sum(mobile) as total_amount,
  count(distinct user_id) as total_users
from
  spendingplatform
where
  mobile is not null and desktop is not null
group by
  spend_date
),

spenddates
as
(
select distinct spend_date from spending
)

select
  s.spend_date,
  'mobile' as platform,
  isnull(mo.total_amount,0) as total_amount,
  isnull(mo.total_users,0) as total_users
from
  spenddates s left join mobileonly mo on s.spend_date = mo.spend_date
union
select
  s.spend_date,
  'desktop' as platform,
  isnull(do.total_amount,0),
  isnull(do.total_users,0)
from
  spenddates s left join desktoponly do on s.spend_date = do.spend_date
union
select
  s.spend_date,
  'both' as platform,
  isnull(b.total_amount,0),
  isnull(b.total_users,0)
from
  spenddates s left join both b on s.spend_date = b.spend_date

