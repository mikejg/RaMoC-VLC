#!/bin/bash

set -e

sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y vim screen 
sudo apt-get install -y ntfs-3g hfsutils hfsprogs
sudo apt-get install -y apache2 php7.0 php7.0-mysql
sudo apt-get install -y mysql-server autofs
sudo apt-get install -y libtag1-dev libqt5sql5-mysql
sudo apt-get install -y libqjson-dev qt5-default 
sudo apt-get install -y wakeonlan dbus-x11 xorg
#sudo apt-get install -y omxplayer wakeonlan
#sudo apt-get install -y libxvidcore4 rsync
sudo apt-get clean -y

#sudo wget https://yt-dl.org/latest/youtube-dl -O /usr/local/bin/youtube-dl
#sudo chmod a+x /usr/local/bin/youtube-dl
#sudo hash -r

### Datenbank Aufsetzen ###
sudo mysql < DataBase/create-database.sql
mysql -u ramocuser -pramoc < DataBase/create-tabels.sql
mysql -u ramocuser -pramoc < DataBase/create-music.sql
sudo cp /etc/mysql/my.cnf /home/pi
sudo sh -c "sed 's/bind-address/#bind-address/g' /etc/mysql/my.cnf >> /tmp/tmp.cnf"
sudo mv /tmp/tmp.cnf /etc/mysql/my.cnf
sudo service mysql restart
#
#### Frabtiefe einstellen ###
#sudo sh -c "/bin/echo \"gpu_mem=128\" >> /boot/config.txt"
#sudo sh -c "/bin/echo \"framebuffer_depth=32\" >> /boot/config.txt"
#sudo sh -c "/bin/echo \"framebuffer_ignore_alpha=1\" >> /boot/config.txt"
sudo sh -c "/bin/echo \"snd_bcm2835\" >> /etc/modules"

cp -a vim ../../.vim
cp vimrc ../../.vimrc
cp screenrc ../../.screenrc
cp xsession ../../.xsession
cp bash_profile ../../.bash_profile

#sudo cp usb-mount@.service /etc/systemd/system/
#sudo cp 99-local.rules /etc/udev/rules.d/
#sudo cp usb-mount.sh /usr/local/bin/
#
#sudo cp -a html /var/www/
#
#cd ../RamocServer
#make clean
#make -j3
#sudo make install
#


