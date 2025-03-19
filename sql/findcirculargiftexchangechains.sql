
-- 3401. Find Circular Gift Exchange Chains
-- https://leetcode.com/problems/find-circular-gift-exchange-chains

-- resource https://sqlsunday.com/2016/04/04/catching-circular-references/







/* Write your T-SQL query statement below */

WITH rcte AS
(
    --- Anchor: any row in SecretSanta could be an anchor in an infinite recursion.
    SELECT giver_id AS start_id,
           receiver_id as id,
           1 as chain_length,
           gift_value as total_gift_value
    FROM SecretSanta

    UNION ALL

    --- Find children. Keep this up until we circle back
    --- to the anchor row, which we keep in the "start_id"
    --- column.
    SELECT rcte.start_id,
           t.receiver_id,
           rcte.chain_length + 1 as chain_length,
           rcte.total_gift_value + t.gift_value as total_gift_value
    FROM rcte
    INNER JOIN SecretSanta AS t ON
        t.giver_id=rcte.id
    WHERE rcte.start_id!=rcte.id
),
start_path_value AS
(
SELECT distinct chain_length, total_gift_value
FROM rcte
WHERE start_id=id
)
select
    row_number() over(order by chain_length desc, total_gift_value desc) as chain_id,
    chain_length,
    total_gift_value
from
    start_path_value




/*

WITH rcte AS
(
    --- Anchor: any row in SecretSanta could be an anchor in an infinite recursion.
    SELECT giver_id AS start_id,
           receiver_id as id,
           CAST(giver_id AS varchar(max)) AS [path]
    FROM SecretSanta

    UNION ALL

    --- Find children. Keep this up until we circle back
    --- to the anchor row, which we keep in the "start_id"
    --- column.
    SELECT rcte.start_id,
           t.receiver_id,
           CAST(rcte.[path]+','+CAST(giver_id AS varchar(max)) AS varchar(max)) AS [path]
    FROM rcte
    INNER JOIN SecretSanta AS t ON
        t.giver_id=rcte.id
    WHERE rcte.start_id!=rcte.id
),
start_path_value AS
(
SELECT start_id, [path]
FROM rcte
WHERE start_id=id
),
-- select * from start_path_value
start_path_split_value
as
(
select
  start_id,
  cs.Value as step --SplitData
from
  start_path_value
cross apply STRING_SPLIT (path, ',') cs
),
start_path_ordered as
(
select
  spsv.start_id,
  stuff((
        select ',' + step
        from start_path_split_value i
        where spsv.start_id = i.start_id
        order by i.step asc
        for xml path('')
    ), 1, 1, ''
  ) as [path]
from
  start_path_split_value spsv
group by
  spsv.start_id
),
unique_chains as
(
select min(start_id) as start_id, [path] from start_path_ordered group by [path]
),
-- at this point we have unique chains and there start id
-- repeat our recursion with those as anchors, counting length and gift value
rcte1 AS
(
    --- Anchor: any row in SecretSanta could be an anchor in an infinite recursion.
    SELECT giver_id AS start_id,
           receiver_id as id,
           CAST(giver_id AS varchar(max)) AS [path],
           gift_value as total_gift_value,
           1 as chain_length
    FROM SecretSanta inner join unique_chains on SecretSanta.giver_id = unique_chains.start_id

    UNION ALL

    --- Find children. Keep this up until we circle back
    --- to the anchor row, which we keep in the "start_id"
    --- column.
    SELECT rcte1.start_id,
           t.receiver_id,
           CAST(rcte1.[path]+','+CAST(giver_id AS varchar(max)) AS varchar(max)) AS [path],
           rcte1.total_gift_value + t.gift_value as total_gift_value,
           rcte1.chain_length + 1 as chain_length
    FROM rcte1
    INNER JOIN SecretSanta AS t ON
        t.giver_id=rcte1.id
    WHERE rcte1.start_id!=rcte1.id
)
-- select * from rcte1 where start_id=id
-- select chain_length, total_gift_value from rcte1 where start_id=id order by chain_length desc, total_gift_value desc
select row_number() over(order by chain_length desc, total_gift_value desc) as chain_id,
  chain_length, total_gift_value from rcte1 where start_id=id

*/
/*
what is commented out give individual correct results per chain involving different path
but the expected result wanted them grouped by value and length simply

*/

OPTION (MAXRECURSION 0);

