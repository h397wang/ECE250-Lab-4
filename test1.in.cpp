new: 4
insert! -1 0  0.3
insert!  0 4  0.3
insert!  0 3 -0.3
insert   0 1  0.3 1
mst      0.3 1
insert   2 3  0.4 1
mst      0.7 2
insert   0 2  0.5 1
mst      1.2 3
insert   1 3  0.1 1
mst      0.8 3
insert   1 3  0.9 1
mst      1.2 3
insert   1 3  0.9 1
mst      1.2 3
delete
summary
