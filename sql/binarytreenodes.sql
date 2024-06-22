
-- 3054. Binary Tree Nodes
-- https://leetcode.com/problems/binary-tree-nodes/




/* Write your T-SQL query statement below */

with root as
(
select N, 'Root' as Type from Tree where P is null
),
leaves as
(
select N, 'Leaf' as Type from Tree where N not in (select ISNULL(P,-1) from Tree) and N not in (select N from root)
),
[inner] as
(
select N, 'Inner' as Type from Tree where N not in (select N from root) and N not in (select N from leaves)
)
select * from root
union
select * from leaves
union
select * from [inner]
order by N
