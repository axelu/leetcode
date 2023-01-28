
-- 1322. Ads Performance
-- https://leetcode.com/problems/ads-performance/


/* Write your T-SQL query statement below */

select
  t.ad_id,
  case
    when t.clicks+t.views = 0 then 0.00 else round(cast(t.clicks as decimal)/(t.clicks+t.views)*100,2)
  end as ctr
from (
    select ad_id,
           isnull(Clicked,0) as clicks,
           isnull(Viewed, 0) as views,
           isnull(Ignored,0) as ignores
    from
    (
      select ad_id,1 as cnt,action from ads
    ) as SourceTable pivot(sum(cnt) for action in (Clicked,Viewed,Ignored)) as PivotTable
  ) as t
order by 'ctr' desc, ad_id
