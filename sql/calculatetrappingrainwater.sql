
-- 3061. Calculate Trapping Rain Water
-- https://leetcode.com/problems/calculate-trapping-rain-water/



/* Write your T-SQL query statement below */


-- find first equal or greater to my left ------------------------------------------------------
with heights_to_left as
(
select
    id,
    height,
    ISNULL((LAG(height) over(order by id)), 0) as left_height
from
    Heights
),
-- select * from heights_to_left
heights_to_left1 as
(
select
    h.id,
    h.height,
    h.left_height,
    (select max(i.id) from Heights as i where i.id < h.id and i.height > h.left_height) as l_id
from
    heights_to_left as h
where
    h.height > h.left_height
),
heights_to_left_w_lid as
(
select
    h.id,
    h.height,
    h.left_height,
    h.l_id,
    t.height as l_height
from
    heights_to_left1 as h join Heights as t on h.l_id = t.id
where
    h.l_id is not NULL
),
-- select * from heights_to_left_w_lid
-- find first equal or greater to my right -----------------------------------------------------
heights_to_right as
(
select
    id,
    height,
    ISNULL((LEAD(height) over(order by id)), 0) as right_height
from
    Heights
),
heights_to_right1 as
(
select
    h.id,
    h.height,
    h.right_height,
    (select min(i.id) from Heights as i where i.id > h.id and i.height > h.right_height) as r_id
from
    heights_to_right as h
where
    h.height > h.right_height
),
heights_to_right_w_rid as -- flip direction to make it same as left
(
select
    h.id,
    h.height,
    h.right_height,
    h.r_id,
    t.height as r_height
from
    heights_to_right1 as h join Heights as t on h.r_id = t.id
where
    h.r_id is not NULL
),
-- select * from heights_to_right_w_rid
-- find first equal or greater to my right in between ----------------------------------------
in_between1r as
(
select
    h.id,
    h.height,
    (select min(i.id) from Heights as i where i.id > h.id + 1 and i.height >= h.height) as r_id
from
    Heights as h
),
in_between2r as
(
select
    h.id,
    h.height,
    (select max(i.height) from Heights as i where i.id > h.id and i.id < h.r_id) as right_height,
    h.r_id,
    t.height as r_height
from
    in_between1r as h join Heights as t on h.r_id = t.id
where
    h.r_id is not NULL
),
in_betweenr as
(
select
    id,
    height,
    right_height,
    r_id,
    r_height
from
    in_between2r
where
    height > right_height
),
-- find first equal or greater to my left in between ----------------------------------------
in_between1l as
(
select
    h.id,
    h.height,
    (select max(i.id) from Heights as i where i.id < h.id - 1 and i.height >= h.height) as l_id
from
    Heights as h
),
in_between2l as
(
select
    h.id,
    h.height,
    (select max(i.height) from Heights as i where i.id < h.id and i.id > h.l_id) as left_height,
    h.l_id,
    t.height as l_height
from
    in_between1l as h join Heights as t on h.l_id = t.id
where
    h.l_id is not NULL
),
in_betweenl as
(
select
    id,
    height,
    left_height,
    l_id,
    l_height
from
    in_between2l
where
    height > left_height
),
-- ----------------------------------------------------------------------------------------------
traps as
(
select
    hl.l_id,
    hl.l_height,
    hl.left_height as height,
    hl.id as r_id,
    hl.height as r_height
from
    heights_to_left_w_lid as hl
union
select
    hr.id as l_id,
    hr.height as l_height,
    hr.right_height as height,
    hr.r_id,
    hr.r_height
from
    heights_to_right_w_rid as hr
union
select
    ibr.id as l_id,
    ibr.height as l_height,
    ibr.right_height as height,
    ibr.r_id,
    ibr.r_height
from
    in_betweenr as ibr
union
select
    ibl.l_id,
    ibl.l_height,
    ibl.left_height as height,
    ibl.id as r_id,
    ibl.height as r_height
from
    in_betweenl as ibl
),
trapped_volume as
(
select
    CASE
        when l_height < r_height
        then (l_height - height) * (r_id - l_id - 1)
        else (r_height - height) * (r_id - l_id - 1)
    END as volume
from
    traps
)
select ISNULL(sum(volume), 0) as total_trapped_water from trapped_volume

/*

{"headers":{"Heights":["id","height"]},"rows":{"Heights":[[1,0],[2,1],[3,0],[4,2],[5,1],[6,0],[7,1],[8,3],[9,2],[10,1],[11,2],[12,1]]}}
{"headers":{"Heights":["id","height"]},"rows":{"Heights":[[1,7],[2,3],[3,2],[4,1],[5,0],[6,1],[7,5]]}}
{"headers":{"Heights":["id","height"]},"rows":{"Heights":[[1,7],[2,7],[3,7],[4,7],[5,7],[6,7],[7,7]]}}
{"headers":{"Heights":["id","height"]},"rows":{"Heights":[[1,7],[2,6],[3,5],[4,4],[5,3],[6,2],[7,1]]}}
{"headers":{"Heights":["id","height"]},"rows":{"Heights":[[1,1],[2,2],[3,3],[4,4],[5,5],[6,6],[7,7]]}}
{"headers":{"Heights":["id","height"]},"rows":{"Heights":[[1,1],[2,2],[3,3],[4,4],[5,3],[6,2],[7,1]]}}
{"headers":{"Heights":["id","height"]},"rows":{"Heights":[[1,2],[2,1],[3,1],[4,0],[5,1],[6,3]]}}
{"headers":{"Heights":["id","height"]},"rows":{"Heights":[[1,4],[2,2],[3,0],[4,3],[5,2],[6,5]]}}
{"headers": {"Heights": ["id", "height"]}, "rows": {"Heights": [[0, 5], [1, 4], [2, 7], [3, 7], [4, 7], [5, 3], [6, 2], [7, 7], [8, 5], [9, 2], [10, 3], [11, 3], [12, 0], [13, 4]]}}

*/
