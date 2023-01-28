
-- 1132. Reported Posts II
-- https://leetcode.com/problems/reported-posts-ii/


/* Write your T-SQL query statement below */

-- spam reports per day
with spam
as
(
select distinct
  post_id,
  action_date
from
  actions
where
  action = 'report' and extra = 'spam'
),
spam_removal
as
(
select
  s.post_id,
  s.action_date,
  case when r.post_id is null then 0 else 1 end as removed
from
  spam s left join removals r on s.post_id = r.post_id
),
removal_percentage
as
(
select
  sr.action_date,
  cast((sum(removed)*100) as decimal)/count(*)  as daily_removal_percentage
from
  spam_removal sr
group by
  sr.action_date
)
select
  round(sum(daily_removal_percentage)/count(*),2) as average_daily_percent
from
  removal_percentage
