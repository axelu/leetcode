
-- 3053. Classifying Triangles by Lengths
-- https://leetcode.com/problems/classifying-triangles-by-lengths/







/* Write your T-SQL query statement below */


select
    case
        when A + B <= C or A + C <= B or B + C <= A
        then
            'Not A Triangle'
        else
            case
                when A = B and A = C
                then
                    'Equilateral'
                else
                    case
                        when A = B or A = C or B = C
                        then
                            'Isosceles'
                        else
                            'Scalene'
                    end
            end
    end as triangle_type
from
    Triangles
