source ~/poky_sdk/environment-setup-cortexa8hf-neon-poky-linux-gnueabi;
mkdir -p toGround;
qemu-arm src/bin/opssat-doom -nosound -nomusic -nosfx -runid 1 -longtics -iwad demos/doom.wad -cdemo demos/zero-e1m1-long -statdump toGround/x.txt;
