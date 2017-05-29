#! /bin/bash
#pvcreate /dev/sdb
#vgcreate /dev/sdb myvg
mkdir -p /mydir_mnt
disks=$(df -hT | grep -Eo "sda[0-9]*")
for disk in $disks
do
fs=$(df -hT | grep -E $disk | awk '{print $2}')
size=$(df -hT | grep -E $disk | awk '{print $3}'| grep -Eo "[^A-Za-z]*" | sed -e  's/,/\./')
unit=$(df -hT | grep -E $disk | awk '{print $3}'| grep -Eo "[A_Za-z]*")
mounted_on=$(df -hT | grep -E $disk | awk '{print $7}')
new_size=$(bc <<< "scale=1;3*$size/2")
#let "new_size = 3 * $size / 2"
#echo $mounted_on
#lvcreate -l "$new_size$unit" -n "l$disk" myvg 
vol_name="/dev/mapper/myvg-l$disk"
#mkfs."$fs" $vol_name
mount  $vol_name  /mydir_mnt
if [ "$mounted_on" != / ]; then
    cp -Rp --preserve=all "$mounted_on/\*" /mydir_mnt
else
    cp -Rp --preserve=all  /* /mydir_mnt
fi
umount $vol_name
if [ "$mounted_on" != /boot ]; then
    echo "$vol_name   $mounted_on $fs defaults 0 0" >> /etc/fstab
fi 
done
#lvcreate --size 1G -n ltmp myvg
home_size=$(du -hs /home | awk '{print $1}' |  grep -Eo "[^A-Za-z]*" | sed -e 's/,/\./')
home_unit=$(du -hs /home | awk '{print $1}' |  grep -Eo "[A-Za-z]*")
lhome_size=$(bc <<< "scale=1;3*$home_size/2")
echo $lhome_size
#lvcreate --size "$lhome_size$home_unit" -n lhome myvg
#mkfs.ext4 /dev/mapper/myvg-ltmp
#mkfs.ext4 /dev/mapper/myvg-lhome
mount /dev/mapper/myvg-ltmp /mydir_mnt
cp -Rp --preserve=all /tmp/* /mydir_mnt
umount /dev/mapper/myvg-ltmp
mount /dev/mapper/myvg-lhome /mydir_mnt
cp -R --preserve=all /home/* /mydir_mnt 
umount /dev/mapper/myvg-lhome
echo "/dev/mapper/myvg-ltmp   /tmp ext4 defaults 0 0" >> /etc/fstab
echo "/dev/mapper/myvg-lhome  /home ext4 defaults 0 0" >> /etc/fstab


