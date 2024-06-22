
-- 2701. Consecutive Transactions with Increasing Amounts
-- https://leetcode.com/problems/consecutive-transactions-with-increasing-amounts/






/* Write your T-SQL query statement below */

-- assume unique (customer_id, transaction_date)

with transactions_start_end as
(
select
    transaction_id,
    customer_id,
    transaction_date,
    amount,
    CASE
        when LAG(transaction_date) over(partition by customer_id order by transaction_date) is not null
        then
            CASE
                when DATEDIFF(dd, LAG(transaction_date) over(partition by customer_id order by transaction_date), transaction_date) > 1
                then 1
                else
                    CASE
                        when LAG(amount) over(partition by customer_id order by transaction_date) >= amount
                        then 1
                        else 0
                    END
            END
        else 1
    END is_start,
    CASE
        when LEAD(transaction_date) over(partition by customer_id order by transaction_date) is not null
        then
            CASE
                when DATEDIFF(dd, transaction_date, LEAD(transaction_date) over(partition by customer_id order by transaction_date)) > 1
                then 1
                else
                    CASE
                        when LEAD(amount) over(partition by customer_id order by transaction_date) <= amount
                        then 1
                        else 0
                    END
            END
        else 1
    END is_end
from
    Transactions
),
transactions_start_end_filtered as
(
select
    tse.customer_id,
    (select max(i.transaction_date)
     from transactions_start_end as i
     where i.customer_id = tse.customer_id and i.is_start = 1 and i.is_end = 0 and i.transaction_date < tse.transaction_date
    ) as consecutive_start,
    tse.transaction_date as consecutive_end
from
    transactions_start_end as tse
where
    tse.is_start = 0 and tse.is_end = 1
)
-- select * from transactions_start_end_filtered

select
    customer_id,
    consecutive_start,
    consecutive_end
from
    transactions_start_end_filtered
where
    DATEDIFF(dd, consecutive_start, consecutive_end) >= 2
order by customer_id
