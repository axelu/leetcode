
-- 1113. Reported Posts
-- https://leetcode.com/problems/reported-posts/


/* Write your T-SQL query statement below */

select
  extra as report_reason,
  count(*) as report_count
from (
    select distinct
      post_id,
      extra
    from
      actions
    where
      action = 'report'
      and action_date = '2019-07-04'
  ) as t
group by extra
