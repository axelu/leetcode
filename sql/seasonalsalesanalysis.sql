
-- 3564. Seasonal Sales Analysis
-- https://leetcode.com/problems/seasonal-sales-analysis/




/* Write your T-SQL query statement below */

with sales_product as
(
select
    s.sale_id,
    s.product_id,
    p.category,
    s.sale_date,
    datepart(month, sale_date) as [month],
    CASE
        when (datepart(month, sale_date) = 12 or datepart(month, sale_date) = 1 or datepart(month, sale_date) = 2)
        then 'Winter'
        else
            CASE
                when (datepart(month, sale_date) = 3 or datepart(month, sale_date) = 4 or datepart(month, sale_date) = 5)
                then 'Spring'
                else
                    CASE
                        when (datepart(month, sale_date) = 6 or datepart(month, sale_date) = 7 or datepart(month, sale_date) = 8)
                        then 'Summer'
                        else 'Fall'
                    END
            END
    END as season,
    s.quantity,
    s.price,
    s.quantity * s.price as total
from
    sales s join products p on s.product_id = p.product_id
),
season_analysis as
(
select
    season,
    category,
    sum(quantity) as total_quantity,
    sum(total) as total_revenue
from
    sales_product
group by
    season, category
),
season_analysis_ranked as
(
select
    RANK() over (partition by season order by total_quantity desc, total_revenue desc) as rnk,
    season,
    category,
    total_quantity,
    total_revenue
 from
    season_analysis
)

select
    season,
    category,
    total_quantity,
    total_revenue
 from
    season_analysis_ranked
where
    rnk = 1
order by
    season
