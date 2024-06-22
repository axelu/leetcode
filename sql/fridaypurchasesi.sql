
-- 2993. Friday Purchases I
-- https://leetcode.com/problems/friday-purchases-i/






/* Write your T-SQL query statement below */

SET DATEFIRST 1;

select
    -- user_id,
    case
        when DATEPART ( mm , DATEADD(day, -7, purchase_date)) <> 11
        then
            1
        else
            case
                when DATEPART ( mm , DATEADD(day, -14, purchase_date)) <> 11
                then
                    2
                else
                    case
                        when DATEPART ( mm , DATEADD(day, -21, purchase_date)) <> 11
                        then
                            3
                        else
                            4
                    end
            end
    end as week_of_month,
    purchase_date,
    sum(amount_spend) as total_amount
from
    Purchases
where
    DATEPART ( yyyy , purchase_date ) = 2023
    and DATEPART ( mm , purchase_date ) = 11
    and DATEPART ( weekday , purchase_date ) = 5 -- Friday
group by
    purchase_date
order by
    purchase_date

