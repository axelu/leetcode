
-- 2020. Number of Accounts That Did Not Stream
-- https://leetcode.com/problems/number-of-accounts-that-did-not-stream/


/* Write your T-SQL query statement below */


select
  count(distinct a.account_id) as accounts_count
from
  subscriptions a
where
  a.start_date < '2022-01-01' and
  a.end_date > '2020-12-31' and
  a.account_id not in (
    select distinct account_id from streams where stream_date > '2020-12-31' and stream_date < '2022-01-01'
  )
