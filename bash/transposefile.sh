
# 194. Transpose File
# https://leetcode.com/problems/transpose-file/


# https://stackoverflow.com/questions/9534744/how-to-transfer-the-data-of-columns-to-rows-with-awk


awk '{
       for (f = 1; f <= NF; f++) { a[NR, f] = $f }
     }
     NF > nf { nf = NF }
     END {
       for (f = 1; f <= nf; f++) {
           for (r = 1; r <= NR; r++) {
               printf a[r, f] (r==NR ? RS : FS)
           }
       }
    }' 194file.txt
