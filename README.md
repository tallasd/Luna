# Luna
An Animal Crossing New Horizons tool to dump Dream Islands.

## Supporting

If you like my work, please consider supporting me on Patreon, thanks!

<p align="center">
<a href="https://www.patreon.com/Ixarus"><img src="https://c5.patreon.com/external/logo/become_a_patron_button.png" alt="Patreon donate button" /> </a>
</p>

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

1. do the thing (run make) or grab a [release](https://github.com/Ixaruz/Luna-ovl/releases/latest).
2. put everything on the SD card and provide 1.7.0 [**DECRYPTED**](https://github.com/Ixaruz/HorizonCrypt/releases/latest) save as template.
3. run overlay when you're on a dream island.
4. grab the dump from your SD card.
5. [**ENCRYPT**](https://github.com/Ixaruz/HorizonCrypt/releases/latest) dump and fix file hashes.
7. ???
8. Profit. 

## Known Issues

- Non-ASCII island names can't be saved (e.g. Japanese/Chinese/Korean/Russian, basically every language that doesnt use the roman alphabet.)
  this is due to Nintendo Switch handling file paths in Shift JIS (basically utf8), which doesn't include non-ASCII characters.
  I wont be able to fix this. Currently Luna just doesn't include the island name in the path, if its invalid, you can still dump foreign islands, duh.

- If you want to go online with dumped dream towns and avoid error 2219-3003 ("Network temporarily unavailable"),
  use your own Island as a template (it should provide proper Netplay information).

## Credits
- **WerWolv** for libtesla and coding help.
- **J-D-K** for JKSV, which was used for testing and also part of its code was used for file handling.
- [**WalteeWartooth**](https://www.reddit.com/user/WalteeWartooth/) for testing Luna and allowing me to dump their island for research!
- [**rabbit_ruby**](https://www.reddit.com/user/rabbit_ruby/) for testing Luna and also breaking my (weak) Revision checker!
