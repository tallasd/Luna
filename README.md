# Luna
An Animal Crossing New Horizons tool to dump Dream Islands.

# SD file structure

    SDMC
    ├── ...
    ├── /config/luna/                                   # config folder for Luna.
    │   ├── /dump/                                      # folder for dumps.
    │   │   ├── /TownName Date @ Time/                  # dump folder format.   Example: "/MyTown 12.12.2020 @ 4.20/"
    │   │   │   ├── /VillagerX/                         # variable amount of players,  0 <= X < 8
    │   │   │   │   ├── /personal.dat
    │   │   │   │   ├── /photo_studio_island.dat
    │   │   │   │   ├── /postbox.dat
    │   │   │   │   └── /profile.dat
    │   │   │   ├── /landname.dat
    │   │   │   └── /main.dat
    │   │   └── ...   
    │   └── /template/                                  # folder for user provided template.
    │       ├── /VillagerX/                             # variable amount of players,  0 <= X < 8; only Villager0 will be used to copy
    │       │   ├── /personal.dat
    │       │   ├── /photo_studio_island.dat
    │       │   ├── /postbox.dat
    │       │   └── /profile.dat
    │       ├── /landname.dat
    │       └── /main.dat
    ├── /switch/.overlays/                              # Tesla-Menu Overlay folder.
    │   └── /Luna-ovl.ovl                               # Luna Overlay.
    └── ...

# How-To

1. do the thing (run make)
2. put stuff on SD card and give 1.6.0 decrypted save as template
3. run overlay when you're on a dream island
4. get yo dump
5. use [HorizonCrypt](https://github.com/Cuyler36/HorizonCrypt) to encrypt yo dump
6. ???
7. Profit. 
