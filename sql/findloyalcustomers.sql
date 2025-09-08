
-- 3657. Find Loyal Customers
-- https://leetcode.com/problems/find-loyal-customers/




/* Write your T-SQL query statement below */

with cust_total_tran_cnt as
(
select distinct
    o.customer_id,
    (select count(*) from customer_transactions i where i.customer_id = o.customer_id) as total_tran_cnt,
    (select count(*) from customer_transactions i where i.customer_id = o.customer_id and i.transaction_type = 'refund') as refund_tran_cnt,
    (select min(transaction_date) from customer_transactions i where i.customer_id = o.customer_id) as min_tran_date,
    (select max(transaction_date) from customer_transactions i where i.customer_id = o.customer_id) as max_tran_date
from
    customer_transactions o
)
select
    customer_id
from
    cust_total_tran_cnt
where
    total_tran_cnt - refund_tran_cnt >= 3
    and datediff(day, min_tran_date, max_tran_date)+1 >= 30
    and refund_tran_cnt / (total_tran_cnt * 1.0) < .2
order by
    customer_id
