
-- 3220. Odd and Even Transactions
-- https://leetcode.com/problems/odd-and-even-transactions/




/* Write your T-SQL query statement below */


with odds as
(
select
    transaction_date,
    sum(amount) odd_sum
from
    transactions
where
    amount % 2 = 1
group by
    transaction_date
),
evens as
(
select
    transaction_date,
    sum(amount) even_sum
from
    transactions
where
    amount % 2 = 0
group by
    transaction_date
),
tranx_dates as
(
select distinct transaction_date from transactions
)
select
    td.transaction_date,
    isnull(o.odd_sum,0) as odd_sum,
    isnull(e.even_sum,0) as even_sum
from
    tranx_dates td left join odds o on td.transaction_date = o.transaction_date
                   left join evens e on td.transaction_date = e.transaction_date
order by
    td.transaction_date
