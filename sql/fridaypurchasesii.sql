
-- 2994. Friday Purchases II
-- https://leetcode.com/problems/friday-purchases-ii/





/* Write your T-SQL query statement below */

SET DATEFIRST 1;

-- Friday's of Nov 2023
with fridays_nov_2023
as
(
select * from ( values (1, convert(date, '2023-11-03'))
                      ,(2, convert(date, '2023-11-10'))
                      ,(3, convert(date, '2023-11-17'))
                      ,(4, convert(date, '2023-11-24')) ) t(week_of_month, purchase_date)
)
select
    f.week_of_month,
    f.purchase_date,
    SUM(ISNULL(p.amount_spend, 0)) as total_amount
from
    fridays_nov_2023 as f left join Purchases as p on f.purchase_date = p.purchase_date
group by
    f.week_of_month, f.purchase_date
order by
    f.week_of_month


-- better solution would be:
-- provide a month and year and construct the dates of the 4 Fridays in that month dynamically
