
-- 3214. Year on Year Growth Rate
-- https://leetcode.com/problems/year-on-year-growth-rate/




/* Write your T-SQL query statement below */

with spend_by_product_by_year as
(
select
    datepart(yyyy, transaction_date) as year,
    product_id,
    sum(spend) as spend
from
    user_transactions
group by
    datepart(yyyy, transaction_date), product_id
),
spend_by_product_by_twoyears as (
select
    year,
    product_id,
    spend as curr_year_spend,
    lag(spend) over(partition by product_id order by year) as prev_year_spend
from
    spend_by_product_by_year
)
select
    year,
    product_id,
    curr_year_spend,
    prev_year_spend,
    CASE
        when prev_year_spend is null
        then null
        else round(((curr_year_spend * 100)/prev_year_spend) - 100, 2)
    END as yoy_rate
from
    spend_by_product_by_twoyears
order by
    product_id, year
