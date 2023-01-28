
-- 1193. Monthly Transactions I
-- https://leetcode.com/problems/monthly-transactions-i/


/* Write your T-SQL query statement below */

with total_trans
as
(
select
  format(trans_date,'yyyy-MM') as month,
  country,
  count(*) as trans_count,
  sum(amount) as trans_total_amount
from
  transactions
group by
  format(trans_date,'yyyy-MM'),country
),
approved_trans
as
(
select
  format(trans_date,'yyyy-MM') as month,
  country,
  count(*) as approved_count,
  sum(amount) as approved_total_amount
from
  transactions
where
  state = 'approved'
group by
  format(trans_date,'yyyy-MM'),country
)
select
  t.month,
  t.country,
  t.trans_count,
  isnull(a.approved_count,0) as approved_count,
  t.trans_total_amount,
  isnull(a.approved_total_amount,0) as approved_total_amount
from
  total_trans t left join approved_trans a on
    t.month = a.month and t.country = a.country
