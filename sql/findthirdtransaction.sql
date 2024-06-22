
-- 2986. Find Third Transaction
-- https://leetcode.com/problems/find-third-transaction/





/* Write your T-SQL query statement below */

with transactions_rnked as
(
select
    rank() over(partition by user_id order by transaction_date) as rnk,
    user_id,
    spend,
    transaction_date
from
    Transactions
),
transactions_plus_prior2 as
(
select
    rnk,
    user_id,
    spend,
    transaction_date,
    LAG(spend) over(partition by user_id order by rnk) as pre,
    LAG(spend,2) over(partition by user_id order by rnk) as prepre
from
    transactions_rnked
-- where
--    rnk = 3
)
select
    user_id,
    spend as third_transaction_spend,
    transaction_date as third_transaction_date
from
    transactions_plus_prior2
where
    rnk = 3
    and spend > pre
    and spend > prepre
order by
    user_id
