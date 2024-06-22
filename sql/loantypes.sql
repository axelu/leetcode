
-- 2990. Loan Types
-- https://leetcode.com/problems/loan-types/



/* Write your T-SQL query statement below */

select distinct user_id
from Loans
where loan_type = 'Refinance' and user_id in (select distinct user_id from Loans where loan_type = 'Mortgage')
