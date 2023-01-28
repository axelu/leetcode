
-- 1811. Find Interview Candidates
-- https://leetcode.com/problems/find-interview-candidates/



/* Write your T-SQL query statement below */

select
  name,
  mail
from
  users
where
  user_id in
  (
    select
      gold_medal as user_id
    from
      contests
    group by
      gold_medal
    having
      count(*) > 2
  ) or
  user_id in
  (
    select distinct
      user_id
    from
    (
    select
      user_id,
      contest_id - row_number() over(partition by user_id order by contest_id) as rep
    from (
        select
          contest_id,
          user_id
        from
          (select contest_id,gold_medal,silver_medal,bronze_medal from contests) p
          unpivot (user_id for medals in (gold_medal,silver_medal,bronze_medal)) as unpvt
        ) t
    ) t
    group by
      user_id,rep
    having
      count(*) > 2
  )
