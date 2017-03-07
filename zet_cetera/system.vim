
[edward@edward]:~/Downloads$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            3.9G     0  3.9G   0% /dev
tmpfs           790M  9.5M  780M   2% /run
/dev/sda1       110G   73G   32G  71% /
tmpfs           3.9G   19M  3.9G   1% /dev/shm
tmpfs           5.0M  4.0K  5.0M   1% /run/lock
tmpfs           3.9G     0  3.9G   0% /sys/fs/cgroup
tmpfs           790M   92K  790M   1% /run/user/1000
[edward@edward]:~/Downloads$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            3.9G     0  3.9G   0% /dev
tmpfs           790M  9.5M  780M   2% /run
/dev/sda1       110G   73G   32G  71% /
tmpfs           3.9G   19M  3.9G   1% /dev/shm
tmpfs           5.0M  4.0K  5.0M   1% /run/lock
tmpfs           3.9G     0  3.9G   0% /sys/fs/cgroup
tmpfs           790M   96K  790M   1% /run/user/1000
/dev/mmcblk0p2   29G  3.2G   24G  12% /media/edward/139ca52c-d45e-44ca-8b8c-12c0af0c9cf5
/dev/mmcblk0p1   63M   21M   42M  33% /media/edward/boot



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

