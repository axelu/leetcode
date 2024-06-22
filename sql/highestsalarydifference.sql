
-- 2853. Highest Salaries Difference
-- https://leetcode.com/problems/highest-salaries-difference/





/* Write your T-SQL query statement below */

declare @mx_marketing int;
set @mx_marketing = (select max(salary) from Salaries where department = 'Marketing');

declare @mx_engineering int;
set @mx_engineering = (select max(salary) from Salaries where department = 'Engineering');


select abs(@mx_marketing - @mx_engineering) as salary_difference;
