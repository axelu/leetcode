
-- 2978. Symmetric Coordinates
-- https://leetcode.com/problems/symmetric-coordinates/


/* Write your T-SQL query statement below */

with coordinates_w_rownbr as
(
select ROW_NUMBER() over(order by X,Y) as id, X, Y from Coordinates
)
select distinct
    o.X,
    o.Y --,
    --i.X as X2,
    --i.Y as Y2
from
    coordinates_w_rownbr as o join coordinates_w_rownbr as i on o.X = i.Y and o.Y = i.X and o.id < i.id
where
    o.X <= o.Y
order by
    o.X, o.Y
    -- o.id
