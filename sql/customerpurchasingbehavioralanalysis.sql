
-- 3230. Customer Purchasing Behavior Analysis
-- https://leetcode.com/problems/customer-purchasing-behavior-analysis/





/* Write your T-SQL query statement below */

with Customers as
(
select distinct customer_id from Transactions
),
TotalSpend as
(
select customer_id, SUM(amount) total_amount from Transactions group by customer_id
),
TransNumber as
(
select
    tx.transaction_id,
    tx.customer_id,
    tx.product_id,
    p.category,
    tx.transaction_date,
    ROW_NUMBER() over (partition by tx.customer_id order by tx.transaction_date) as transaction_count
from
    Transactions tx join Products p on tx.product_id = p.product_id
),
TransCount as
(
select
    customer_id,
    MAX(transaction_count) as transaction_count
from
    TransNumber
group by
    customer_id
),
CategoryCount as
(
select
    tn.customer_id,
    tn.category,
    count(*) as category_count,
    max(tn.transaction_date)  as category_last_date
from
    TransNumber tn
group by
    tn.customer_id,
    tn.category
),
CategoryRank as
(
select
    customer_id,
    category,
    category_count,
    category_last_date,
    ROW_NUMBER() over(partition by customer_id order by category_count desc, category_last_date desc) as rnk -- what is the next tie breaker ???
from
    CategoryCount
),
CategoryCountUnique as
(
select customer_id, count(*) as unique_categories from CategoryCount group by customer_id
),
Result as
(
select
    c.customer_id,
    ts.total_amount,
    tc.transaction_count,
    ccu.unique_categories,
    round(ts.total_amount / cast(tc.transaction_count as decimal),2) as avg_transaction_amount,
    cr.category as top_category,
    round(((tc.transaction_count * 10) + (ts.total_amount / 100.0)),2) as loyalty_score
from
    Customers c join TotalSpend ts on ts.customer_id = c.customer_id
        join TransCount tc on tc.customer_id = c.customer_id
        join CategoryRank cr on cr.customer_id = c.customer_id and cr.rnk = 1
        join CategoryCountUnique ccu on ccu.customer_id = c.customer_id
)

select * from Result order by loyalty_score desc, customer_id
