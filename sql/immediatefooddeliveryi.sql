
-- 1173. Immediate Food Delivery I
-- https://leetcode.com/problems/immediate-food-delivery-i/



/* Write your T-SQL query statement below */

declare @nbr_immediate_orders float;
set @nbr_immediate_orders = (
  select count(*)
  from delivery
  where order_date = customer_pref_delivery_date
);

declare @nbr_total_orders float;
set @nbr_total_orders = (
  select count(*)
  from delivery
);

select cast(format(@nbr_immediate_orders/@nbr_total_orders*100,'N2') as float) as immediate_percentage;
