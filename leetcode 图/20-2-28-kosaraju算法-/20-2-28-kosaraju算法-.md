## POJ2942

Knights of the Round Table

| **Time Limit:** 7000MS       |      | **Memory Limit:** 65536K |
| ---------------------------- | ---- | ------------------------ |
| **Total Submissions:** 16505 |      | **Accepted:** 5458       |

Description

Being a knight is a very attractive career: searching for the Holy Grail, saving damsels in distress, and drinking with the other knights are fun things to do. Therefore, it is not very surprising that in recent years the kingdom of King Arthur has experienced an unprecedented increase in the number of knights. There are so many knights now, that it is very rare that every Knight of the Round Table can come at the same time to Camelot and sit around the round table; usually only a small group of the knights isthere, while the rest are busy doing heroic deeds around the country.

Knights can easily get over-excited during discussions-especially after a couple of drinks. After some unfortunate accidents, King Arthur asked the famous wizard Merlin to make sure that in the future no fights break out between the knights. After studying the problem carefully, Merlin realized that the fights can only be prevented if the knights are seated according to the following two rules:

- The knights should be seated such that two knights who hate each other should not be neighbors at the table. (Merlin has a list that says who hates whom.) The knights are sitting around a roundtable, thus every knight has exactly two neighbors.
- An odd number of knights should sit around the table. This ensures that if the knights cannot agree on something, then they can settle the issue by voting. (If the number of knights is even, then itcan happen that ``yes" and ``no" have the same number of votes, and the argument goes on.)

Merlin will let the knights sit down only if these two rules are satisfied, otherwise he cancels the meeting. (If only one knight shows up, then the meeting is canceled as well, as one person cannot sit around a table.) Merlin realized that this means that there can be knights who cannot be part of any seating arrangements that respect these rules, and these knights will never be able to sit at the Round Table (one such case is if a knight hates every other knight, but there are many other possible reasons). If a knight cannot sit at the Round Table, then he cannot be a member of the Knights of the Round Table and must be expelled from the order. These knights have to be transferred to a less-prestigious order, such as the Knights of the Square Table, the Knights of the Octagonal Table, or the Knights of the Banana-Shaped Table. To help Merlin, you have to write a program that will determine the number of knights that must be expelled.



Input

The input contains several blocks of test cases. Each case begins with a line containing two integers 1 ≤ n ≤ 1000 and 1 ≤ m ≤ 1000000 . The number n is the number of knights. The next m lines describe which knight hates which knight. Each of these m lines contains two integers k1 and k2 , which means that knight number k1 and knight number k2 hate each other (the numbers k1 and k2 are between 1 and n ).

The input is terminated by a block with n = m = 0 .



Output

For each test case you have to output a single integer on a separate line: the number of knights that have to be expelled.



Sample Input

```
5 5
1 4
1 5
2 5
3 4
4 5
0 0
```

Sample Output

```
2
```

Hint

Huge input file, 'scanf' recommended to avoid TLE.

Source

[Central Europe 2005](http://poj.org/searchproblem?field=source&key=Central+Europe+2005)



* n个人坐在圆桌旁边, 1<=n<=1000, 1<=m<=1M, m组关系(a, b), 每个关系表示a恨b, 所以ab不能坐一块, 另外, 坐在圆桌山的人得是奇数. 去除多少人可以满足上述条件. 
* 双连通分量
    * (代码)[https://www.cnblogs.com/kamimxr/p/11053539.html]
    * 未完(待续)

---

