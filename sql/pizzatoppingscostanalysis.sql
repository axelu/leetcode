
-- 3050. Pizza Toppings Cost Analysis
-- https://leetcode.com/problems/pizza-toppings-cost-analysis/





/* Write your T-SQL query statement below */

with combinations as
(
select
    t1.topping_name as topping_name1, t1.cost as cost1,
    t2.topping_name as topping_name2, t2.cost as cost2,
    t3.topping_name as topping_name3, t3.cost as cost3
from Toppings as t1 join
     Toppings as t2
     on t2.topping_name > t1.topping_name join
     Toppings as t3
     on t3.topping_name > t2.topping_name
)
select
    topping_name1 + ',' + topping_name2 + ',' + topping_name3 as pizza,
    cost1 + cost2 + cost3 as total_cost
from
    combinations
order by
    cost1 + cost2 + cost3 desc, (topping_name1 + ',' + topping_name2 + ',' + topping_name3)
