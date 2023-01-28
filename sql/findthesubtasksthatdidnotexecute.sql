
-- 1767. Find the Subtasks That Did Not Execute
-- https://leetcode.com/problems/find-the-subtasks-that-did-not-execute/


/* Write your T-SQL query statement below */

-- it is guaranteed that 2 <= subtasks_count <= 20

with subtask_ids -- 1 to 20
as
(
select * from ( values
        (1),(2),(3),(4),(5),(6),(7),(8),(9),(10),(11),(12),(13),(14),(15),(16),(17),(18),(19),(20)
    ) t(subtask_id)
),
all_subtasks
as
(
select
  t.task_id,
  i.subtask_id
from
  tasks t join subtask_ids i on t.subtasks_count >= i.subtask_id
)
select
  a.task_id,
  a.subtask_id
from
  all_subtasks a left join executed e on a.task_id = e.task_id and a.subtask_id = e.subtask_id
where
  e.subtask_id is null

