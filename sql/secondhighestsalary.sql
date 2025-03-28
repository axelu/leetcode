
-- 176. Second Highest Salary
-- https://leetcode.com/problems/second-highest-salary/




# Write your MySQL query statement below
SELECT
    IFNULL(
      (SELECT DISTINCT Salary
       FROM Employee
       ORDER BY Salary DESC
        LIMIT 1 OFFSET 1),
    NULL) AS SecondHighestSalary
