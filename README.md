# Luna
An Animal Crossing New Horizons tool to dump Dream Islands.

# SD file structor

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
