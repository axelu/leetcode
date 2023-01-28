
-- 1205. Monthly Transactions II
-- https://leetcode.com/problems/monthly-transactions-ii/



/* Write your T-SQL query statement below */


-- approved transactions
with approved
as
(
select
  format(trans_date,'yyyy-MM') as month,
  country,
  count(*) as approved_count,
  sum(amount) as approved_amount
from
  transactions
where
  state = 'approved'
group by
  format(trans_date,'yyyy-MM'),
  country
),
-- chargeback transactions
chargeback
as
(
select
  format(c.trans_date,'yyyy-MM') as month,
  t.country,
  count(*) as chargeback_count,
  sum(t.amount) as chargeback_amount
from
  transactions t join chargebacks c on t.id = c.trans_id
group by
  format(c.trans_date,'yyyy-MM'),
  t.country
)
select
  a.month,
  a.country,
  a.approved_count,
  a.approved_amount,
  isnull(c.chargeback_count,0) as chargeback_count,
  isnull(c.chargeback_amount,0) as chargeback_amount
from
  approved a left join chargeback c on a.month = c.month and a.country = c.country
union
select
  c.month,
  c.country,
  isnull(a.approved_count,0),
  isnull(a.approved_amount,0),
  c.chargeback_count,
  c.chargeback_amount
from
  chargeback c left join approved a on c.month = a.month and c.country = a.country
