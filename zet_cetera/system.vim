

[edward@edward]:/media/edward/0F76-2DD9$ sudo dd bs=4M if=/home/edward/2017-03-02-raspbian-jessie.img of=/dev/mmcblk0p1 status=progress



[edward@edward]:/media/edward/0F76-2DD9$ sudo dd bs=4M if=/dev/mmcblk0p1 of=/home/edward/Downloads/copy.img status=progress
[sudo] password for edward: 
31096569856 bytes (31 GB, 29 GiB) copied, 1152.15 s, 27.0 MB/s
7415+0 레코드 들어옴
7415+0 레코드 나감
31100764160 bytes (31 GB, 29 GiB) copied, 1152.29 s, 27.0 MB/s



[edward@edward]:~/Downloads$ sudo truncate --reference 2017-03-02-raspbian-jessie.img copy.img 
[sudo] password for edward: 



[edward@edward]:~/Downloads$ diff -s copy.img 2017-03-02-raspbian-jessie.img 

Files copy.img and 2017-03-02-raspbian-jessie.img are identical


[edward@edward]:~/Downloads$ sync

