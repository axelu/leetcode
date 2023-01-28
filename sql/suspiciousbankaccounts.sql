
-- 1843. Suspicious Bank Accounts
-- https://leetcode.com/problems/suspicious-bank-accounts/




/* Write your T-SQL query statement below */

with monthly
as
(
select
  account_id,
  datepart(year,day) as year,
  datepart(month,day) as month,
  sum(amount) as sum_credits
from
  transactions
where
  type = 'Creditor'
group by
  account_id,datepart(year,day),datepart(month,day)
),
monthlyplus
as
(
select
  monthly.account_id,
  monthly.year as year,
  monthly.month as month,
  monthly.sum_credits as credits,
  isnull(p.sum_credits,0) as prior_month_credits
from
  monthly left join monthly p on
    monthly.account_id = p.account_id and
    ( (monthly.year = p.year and monthly.month = p.month+1) or
      (monthly.year = p.year+1 and monthly.month = 1 and p.month = 12)
    )
)
select distinct
  t.account_id
from
  monthlyplus t
where
  t.credits > (select i.max_income from accounts i where i.account_id = t.account_id) and
  t.prior_month_credits > (select i.max_income from accounts i where i.account_id = t.account_id)
order by
  t.account_id
