#!/bin/bash

if [ -z "$1" ]
then
      echo "Usage: createPackage.sh versionNumber"
else
(
  cd .. || exit
  idf.py clean
  idf.py build
)

(
  cd ../RecoveryFirmware || exit
  idf.py clean
  idf.py build
)

mkdir "$1"
(
cd "$1" || exit
cp ../../RecoveryFirmware/build/bootloader/bootloader.bin                   bootloader.bin
cp ../../RecoveryFirmware/build/partition_table/partition-table.bin         partition-table.bin
cp ../../RecoveryFirmware/build/ota_data_initial.bin                        ota_data_initial.bin
cp ../../RecoveryFirmware/build/BootloaderStub.bin                          BootloaderStub.bin

echo "esptool.py -b 460800 --before default_reset\
 --after hard_reset --chip esp32  write_flash --flash_mode dio\
  --flash_size 4MB --flash_freq 80m 0x1000 bootloader.bin\
   0x6000 partition-table.bin 0x7000 ota_data_initial.bin\
    0x10000 BootloaderStub.bin" > flash.sh

echo "esptool.py -b 460800 --before default_reset\
 --after hard_reset --chip esp32  write_flash --flash_mode dio\
  --flash_size 4MB --flash_freq 80m 0x1000 bootloader.bin\
   0x6000 partition-table.bin 0x7000 ota_data_initial.bin\
    0x10000 BootloaderStub.bin" > flash.ps1
)

zip -r Recovery_"$1".zip "$1"
rm -r "$1"

zip -r Firmware_"$1".zip ../build/Firmware.bin

fi

if [ -z "$2" ]
then
    echo "To publish, call createPackage.sh versionNumber -p"
else

    curl --user "$crappyPLCUserAuth":"$crappyPLCUserPass"\
     --upload-file "$(pwd)"/Recovery_"$1".zip\
      https://alexanastasiu.com/git/api/packages/"$crappyPLCUserAuth"/generic/CrappyPLC-Recovery/"$1"/"$1".zip

    curl --user "$crappyPLCUserAuth":"$crappyPLCUserPass"\
     --upload-file "$(pwd)"/Firmware_"$1".zip\
      https://alexanastasiu.com/git/api/packages/"$crappyPLCUserAuth"/generic/CrappyPLC-Firmware/"$1"/Firmware_"$1".bin
fi

