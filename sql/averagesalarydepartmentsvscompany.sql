
-- 615. Average Salary: Departments VS Company
-- https://leetcode.com/problems/average-salary-departments-vs-company/





/* Write your T-SQL query statement below */

with company_avg
as
(
select
  format(s.pay_date,'yyyy-MM') as pay_month,
  cast(sum(s.amount) as decimal)/count(*) as avg
from
  salary s
group by
  format(s.pay_date,'yyyy-MM')
),
department_avg
as
(
select
  format(s.pay_date,'yyyy-MM') as pay_month,
  e.department_id,
  cast(sum(s.amount) as decimal)/count(*) as avg
from
  salary s join employee e on s.employee_id = e.employee_id
group by
  e.department_id,format(s.pay_date,'yyyy-MM')
)
select
  da.pay_month,
  da.department_id,
  case
    when da.avg > ca.avg then 'higher'
    when da.avg = ca.avg then 'same' else 'lower'
  end as comparison
from
  department_avg da join company_avg ca on da.pay_month = ca.pay_month
