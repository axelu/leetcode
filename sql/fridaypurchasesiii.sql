
-- 3118. Friday Purchase III
-- https://leetcode.com/problems/friday-purchase-iii/


/* Write your T-SQL query statement below */


SET DATEFIRST 1;

-- Friday's of Nov 2023
with fridays_nov_2023 as
(
select * from ( values (1, convert(date, '2023-11-03'))
                      ,(2, convert(date, '2023-11-10'))
                      ,(3, convert(date, '2023-11-17'))
                      ,(4, convert(date, '2023-11-24')) ) t(week_of_month, purchase_date)
),
memberships as -- only the ones we are interested in
(
select * from ( values ('VIP'),('Premium') ) t(membership)
),
fridays_nov_2023_wmembership as
(
select
    f.week_of_month,
    f.purchase_date,
    m.membership
from
    fridays_nov_2023 as f cross join memberships as m
),
purchases_wmembership as
(
select
    p.user_id,
    u.membership,
    p.purchase_date,
    p.amount_spend
from
    Purchases as p join Users u on p.user_id = u.user_id
)
select
    f.week_of_month,
    f.membership,
    SUM(ISNULL(p.amount_spend, 0)) as total_amount
from
    fridays_nov_2023_wmembership as f left join purchases_wmembership as p on f.purchase_date = p.purchase_date and f.membership = p.membership
group by
    f.week_of_month, f.membership
order by
    f.week_of_month, f.membership


-- better solution would be:
-- provide a month and year and construct the dates of the 4 Fridays in that month dynamically
