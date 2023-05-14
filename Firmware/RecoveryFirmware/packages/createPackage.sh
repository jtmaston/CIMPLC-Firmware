if [ -z "$1" ]
then
      echo "Usage: createPackage.sh versionNumber"
else
mkdir "$1"
# shellcheck disable=SC2164
cd "$1"
cp ../../build/bootloader/bootloader.bin                   bootloader.bin
cp ../../build/partition_table/partition-table.bin         partition-table.bin
cp ../../build/ota_data_initial.bin                        ota_data_initial.bin
cp ../../build/BootloaderStub.bin                          BootloaderStub.bin

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

cd ..
zip -r $1.zip $1
rm -r $1

fi

if [ -z "$2" ]
then
    echo "To publish, call createPackage.sh versionNumber -p"
else

    curl --user "$crappyPLCUserAuth":"$crappyPLCUserPass"\
     --upload-file "$(pwd)"/"$1".zip\
      https://alexanastasiu.com/git/api/packages/"$crappyPLCUserAuth"/generic/CrappyPLC/"$1"/"$1".zip
fi

