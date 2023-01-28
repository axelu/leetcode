
-- 1613. Find the Missing IDs
-- https://leetcode.com/problems/find-the-missing-ids/


/* Write your T-SQL query statement below */

declare @mxid int;
set @mxid = (select max(customer_id) from customers);

with consecutive (cid)
as
(
    select 1 as cid
    union all
    select cid + 1
    from consecutive
    where cid < @mxid
)
select cid as ids
from consecutive
where cid not in (select customer_id from customers)
