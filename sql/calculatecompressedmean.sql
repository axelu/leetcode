
-- 2985. Calculate Compressed Mean
-- https://leetcode.com/problems/calculate-compressed-mean/





/* Write your T-SQL query statement below */

select
    round(cast(sum(item_count * order_occurrences) as decimal)/sum(order_occurrences),2) as average_items_per_order
from
    Orders
