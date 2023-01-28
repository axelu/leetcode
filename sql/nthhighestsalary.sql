
-- 177. Nth Highest Salary
-- https://leetcode.com/problems/nth-highest-salary/


CREATE FUNCTION getNthHighestSalary(@N INT) RETURNS INT AS
BEGIN

    RETURN (
       select
         distinct t.salary
       from (
           select
             salary,
             dense_rank() over(order by salary desc) as rnk
           from
             employee
       ) t
       where rnk = @N
    );
END
