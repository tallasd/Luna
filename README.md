# Luna
An Animal Crossing New Horizons tool to dump Dream Islands.

## SD file structure

    SDMC
    ├── ...
    ├── /config/luna/                                   # config folder for Luna.
    │   ├── /dump/                                      # folder for dumps.
    │   │   ├── /[DREAM_ADDRESS] TownName/              # dump folder format. Example: "/[DA-XXXX-XXXX-XXXX] MyTown
    │   │   │   ├──/Date @ Time (in dream)/             #                               /12.12.2020 @ 4.20/"
    │   │   │   │   ├── /VillagerX/                     # variable amount of players,  0 <= X < 8
    │   │   │   │   │   ├── /personal.dat
    │   │   │   │   │   ├── /photo_studio_island.dat
    │   │   │   │   │   ├── /postbox.dat
    │   │   │   │   │   └── /profile.dat
    │   │   │   │   ├── /landname.dat
    │   │   │   │   └── /main.dat
    │   │   │   └── ...   
    │   │   └── ...   
    │   └── /template/                                  # folder for user provided template.
    │       ├── /VillagerX/                             # variable amount of players,  0 <= X < 8; 
    │       │   ├── /personal.dat                       # only Villager0 will be used to copy
    │       │   ├── /photo_studio_island.dat
    │       │   ├── /postbox.dat
    │       │   └── /profile.dat
    │       ├── /landname.dat
    │       └── /main.dat
    ├── /switch/.overlays/                              # Tesla-Menu Overlay folder.
    │   └── /Luna-ovl.ovl                               # Luna Overlay.
    └── ...

## How-To

1. do the thing (run make) or grab a [release](https://github.com/Ixaruz/Luna-ovl/releases/latest)
2. put stuff on SD card and give 1.6.0 decrypted save as template
3. run overlay when you're on a dream island
4. get yo dump
5. use [HorizonCrypt](https://github.com/Cuyler36/HorizonCrypt) to encrypt yo dump
6. Open and Save the encrypted data with [NHSE](https://github.com/kwsch/NHSE) to fix Hashes etc.
7. ???
8. Profit. 

## Known Issues

- non-ASCII island names can't be saved (e.g. Japanese/Chinese/Korean/Russian, basically every language that doesnt use the roman alphabet.)
  this is due to Nintendo Switch handling file paths in Shift JIS (basically utf8), which doesn't include non-ASCII characters.
  I wont be able to fix this. Currently Luna just doesn't include the island name in the path, if its invalid, you can still dump foreign islands, duh.

## Credits
- **WerWolv** for libtesla and coding help.
- **J-D-K** for JKSV, which was used for testing and also part of its code was used for file handling.
