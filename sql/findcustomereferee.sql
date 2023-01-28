
-- 584. Find Customer Referee
-- https://leetcode.com/problems/find-customer-referee/


/* Write your T-SQL query statement below */

select
    name
from
    customer
where
    referee_id is null or referee_id <> 2
