
-- 1821. Find Customers With Positive Revenue this Year
-- https://leetcode.com/problems/find-customers-with-positive-revenue-this-year/


/* Write your T-SQL query statement below */

select customer_id
from customers
where year = 2021 and
  revenue > 0
