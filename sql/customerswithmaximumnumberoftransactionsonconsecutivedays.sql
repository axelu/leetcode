
-- 2752. Customers with Maximum Number of Transactions on Consecutive Days
-- https://leetcode.com/problems/customers-with-maximum-number-of-transactions-on-consecutive-days/





/* Write your T-SQL query statement below */

/*
 oberservation
 example
 {"headers":{"Transactions":["transaction_id","customer_id","transaction_date","amount"]},"rows":{"Transactions":[[1,101,"2023-05-01",100],[2,101,"2023-05-02",150],[3,101,"2023-05-03",200],[4,102,"2023-05-01",50],[5,102,"2023-05-03",100],[6,102,"2023-05-04",200],[7,105,"2023-05-01",100],[8,105,"2023-05-02",150],[9,105,"2023-05-03",200]]}}
 customer 101 made 3 transactions on 3 consecutive days, so did customer 105

 but here, customer 101 made 4 transactions on 3 consecutive days, customer 105 made 3 transactions on 3 consecutive days,
 BUT the expected result is still customer 101 AND customer 105, unclear why
 {"headers":{"Transactions":["transaction_id","customer_id","transaction_date","amount"]},"rows":{"Transactions":[[1,101,"2023-05-01",100],[2,101,"2023-05-01",100],[2,101,"2023-05-02",150],[3,101,"2023-05-03",200],[200,102,"2023-05-01",50],[5,102,"2023-05-03",100],[201,102,"2023-05-04",200],[500,105,"2023-05-01",100],[501,105,"2023-05-02",150],[503,105,"2023-05-03",200]]}}

 maybe we can assume that a give customer can only have 1 transaction per day ???
 hint in problem description
 Each row contains information about transactions that includes unique (customer_id, transaction_date) along with the corresponding customer_id and amount.

 here customer 101 only making two transaction on the same day
{"headers":{"Transactions":["transaction_id","customer_id","transaction_date","amount"]},"rows":{"Transactions":[[1,101,"2023-05-01",100],[2,101,"2023-05-01",150]]}}
expected result
{"headers": ["customer_id"], "values": [[101], [101]]}   <- that does not make any sense, but does support assumption that customer_id, transaction_date is unique


 */

with transactions_start_end as
(
select
    transaction_id,
    customer_id,
    transaction_date,
    CASE
        when LAG(transaction_date) over(partition by customer_id order by transaction_date) is not null
        then
            CASE
                when DATEDIFF(dd, LAG(transaction_date) over(partition by customer_id order by transaction_date), transaction_date) > 1
                then 1
                else 0
            END
        else 1
    END as is_start,
    CASE
        when LEAD(transaction_date) over(partition by customer_id order by transaction_date) is not null
        then
            CASE
                when DATEDIFF(dd, transaction_date, LEAD(transaction_date) over(partition by customer_id order by transaction_date)) > 1
                then 1
                else 0
            END
        else 1
    END as is_end
from
    Transactions
),
-- select * from transactions_start_end

transactions_start_end_filtered as
(
select
    tse.customer_id,
    tse.transaction_date,
    tse.is_start,
    tse.is_end,
    CASE
        when tse.is_start = 1 and tse.is_end = 1
        then 1
        else
            CASE
                when tse.is_end = 0
                then 0
                else DATEDIFF(dd, (
                                    select max(i.transaction_date)
                                    from transactions_start_end as i
                                    where i.customer_id = tse.customer_id and i.is_start = 1 and i.transaction_date < tse.transaction_date
                                   ),
                              tse.transaction_date
                     ) + 1
            END
    END as consecutive_days
from
    transactions_start_end as tse
where
    tse.is_start = 1 OR tse.is_end = 1
)
select
    customer_id
from
    transactions_start_end_filtered
where
    consecutive_days = (select max(consecutive_days) from transactions_start_end_filtered)
order by
    customer_id

