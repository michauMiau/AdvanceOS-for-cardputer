# AdvanceOS
Music Player
<img src="gitFiles/screen_105219.bmp?raw=true">
<img src="gitFiles/screen_71496.bmp?raw=true">
File explorer 
<img src="gitFiles/screen_9116.bmp?raw=true">
<img src="gitFiles/screen_97751.bmp?raw=true">
paint
<img src="gitFiles/screen_100373.bmp?raw=true">
<img src="gitFiles/screen_223244.bmp?raw=true">
<img src="gitFiles/screen_370307.bmp?raw=true">
talk to (not) AI chatbot
<img src="gitFiles/screen_11139.bmp?raw=true">
<img src="gitFiles/screen_21074.bmp?raw=true">
3D renderer OBG
<img src="gitFiles/screen_34278.bmp?raw=true">
Games ARDUBOY NES GBC
<img src="gitFiles/screen_153126.bmp?raw=true">
Wifi Spectrum
<img src="gitFiles/screen_27807.bmp?raw=true">
Partition Viewer
<img src="gitFiles/screen_42323.bmp?raw=true">




AdvanceOS is a lightweight operating system for the CardputerADV, designed primarily for media playback and file browsing.
Currently, it supports MP3 and WAV playback. In the future, Text editor and lots's of cool stuff!
Upcoming features include text viewing and editing, as well as image display capabilities.

# Supported Files

* MP3 WAV : music files
* IR : infra red code files (to emit infrared code)
* GIF PNG JPEG BMP(slow): picture files
* TXT JSON CONF : text files (i can add more files type if you like. you can ask in issues Section)
* OBJ MTL : 3D Model files
* ESPRC : esp remote control files to controll other esp project remotly See WIKI
* ARD arduboy game
* NES nes games
* GBC GB old gameboy and gameboy color games


## 🚀 Installation Options

* Option 1: Manual Flashing
Download the latest .bin file from the Releases section and flash it using the ESP Flash Download Tool.
Instructions and download link: [ESP Flash Download Tool](https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32/production_stage/tools/flash_download_tool.html)
* Option 2: Recommended – M5Burner
Use M5Burner:
Select Cardputer from the sidebar, search for AdvanceOS, and install it directly.
* Option 3: Using the Launcher
If you already have the Launcher installed on your Cardputer, you can install AdvanceOS via SD card:
 Download the latest .bin file
 Copy it to your SD card
 Use the Launcher to install it
More info: [Launcher GitHub](https://github.com/bmorcelli/Launcher)

# Very Importent
if after some use,in some menu not open (like Remote ESP or Record that demand lot's of RAM) it mean it out of memory restart the cardputer and enter directly to the menu and it will work!


# 🎮 How to Use
- A microSD card is required. The file system must be FAT or FAT32). NTFS and exFAT are not supported. (New card (Fast 
How to format to FAT https://www.instructables.com/Format-USB-Flash-Drive-to-FATFAT16-not-FAT32/
- Navigation is simple:
- ESC → Go back
- Enter → Select
# in file system

- ENTER open file menu
- -> fast execute file

# in Text editor
- FN + Left Arrow : move curser to left 
- FN + right Arrow : move curser to right 
- FN + Up Arrow : scroll text
- FN + Down Arrow : scroll text
- ESC open Menu
# in paint mode BETA
- Arrows move courser
- ESC open menu
- ENTER Paint / Accept in menu
- +/- change brush size
- B brush mode
- L line mode
- T triangle mode
- I Eyedropper mode
- K enter text (depend on brush size try 1 2 or 3
- U circle mode
- G bucket mode (draw on in color area)
- S squre mode
- E ellipse mode
- F toggle fill mode (if not fill only draw outline)
# in Game
- ESC exit the game and back to file explorer 
- Arrow key
- Z is A button
- X is B button
- ENTER is START button
- BACKSPACE / DEL button is SELECT button
- in emulator NES or GBC also "L" and "K" "1" and "2" and "WASD" keys suppurted

# in Media Player
- [ back 7 second
- ] forward 7 second
- -> move next song
- <- move back song
- PLUS key + or MINUS key _ to change volume

# in 3D renderer
* use file 3d file example from 3D_MODEL folder or create yourself in 3D software like BLENDER
* 1 key normal view press again to change beckground
* 2 key Grey view like Blendrer software
* 3 key wireframe view
- Arrow keys to rotate
- E S D A move camera , arrows key rotate camera
- W or R keys move up or down

# 🛠️ Planned Features
- [X] 3d render , it can play small OBJ files, you can use models in 3D_MODEL folder( it render simple materials like colors in faces not Texture!, the materials is in MTL files near the OBJ file, they must be the same name to load the materials), you can create 3d model in blender, export as OBJ, you can assing simple shader like color and assing to the faces, if the load freeze maybe it's too large file, (FPS added to see how the CARDPUTER can handle it)
- [X] File management: delete, copy,  files DONE!! 
- [X] Text editor: view create and edit .txt .json .conf files DONE!!
- [x] paint mode draw new picture or edit old pictur
- [X] Timer functionality
- [X] Step's Counter!
- [x] Image viewer (PNG ,GIF,JPEG) can zoom in and out and pan image by arrow keys and +/- keys(need small size PIC limited by Cardputer RAM)
- [x] GIF viewer work with animation (need small size GIF ,Cardputer RAM is limited)
- [x] Notes for daily use
- [x] mic record to SD card
- [x] ESP project remote control see more info [here](https://github.com/bomberman30/AdvanceOS-for-cardputer/wiki)
- [ ] radio (Maybe)
- [x] IR Sender Put IR files in sd card and send via the cardputer you can find IR files [here](https://github.com/Lucaslhm/Flipper-IRDB)
- [x] Screenshot press FN+S everywere to take screenshot (will be save in AdvaneOS folder)
- [x] Custom theme you can create themes and select them ! enter extra menu-> theme manager You can add custom picture to every Menu download  TEST_TEHEME folder and put in SD card Activate it in file explorer, you can edit the PNG files as you like and edit the thm file via the cardputer itself
- [X] Games!! you can Download Arduboy games or NES or GBC games (you need to put "Emulator.extension" file in "AdvanceOS" folder in your SD card) (put the games in "Games" folder in the root of the SD card to see the games in GAME menu, or just run the games via file explorer) if you install AdvanceOS via launcher you need to change partition type to anable the games to work!!!! the OS will ask it Automatic to change if you enter to Games in main menu.
- you can add picture to a game in game menu!! 
how to add??
if your game is MARIO.nes Create PNG file and rename it MARIO.png
the image must be 135X135 size and PNG format , the image need to be in the same "Games" folder


#💡 Suggestions are Welcome!
If you have practical ideas or feature requests, feel free to share!


