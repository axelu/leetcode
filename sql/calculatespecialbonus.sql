

# 1873. Calculate Special Bonus
# https://leetcode.com/problems/calculate-special-bonus/


# Write your MySQL query statement below


select
    employee_id as employee_id,
    case
        when employee_id % 2 != 0 && substr(name,1,1) != "M" then salary
        else 0
    end as bonus
from
    Employees
order by
    employee_id



