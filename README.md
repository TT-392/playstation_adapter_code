# Taiko no Tatsujin PlayStation adapter code
This repository contains the code for [this](https://github.com/TT-392/playstation_adapter_pcb) project. The software so far only supports the Taiko no Tatsujin PlayStation controller.

## Flashing the code
These instructions assume you have an assembled PlayStation adapter, and have acquired the compiled firmware in the form of a .uf2 file (can be found in the GitHub releases tab).

1. Connect the adapter to the pc, while holding down the button on the adapter. The adapter should now show up on your computer as a "USB mass storage device", aka, a USB stick. (If your OS does not automatically mount USB sticks, you should do so yourself, but you probably know that already if you are in that situation).

2. Now, drag the .uf2 file into that USB stick. The USB stick should now unmount, and the adapter should now reboot, with the new firmware, and show up on your pc as a HID keyboard device.

## Changing the keybinds
The adapter acts like a USB keyboard, using the keys D, F, J, K, Escape and Enter keys. Depending on your situation, you might want to change these keybinds. The process of doing this goes as follows.

1. Connect the adapter to the pc.

2. The adapter is both a HID keyboard, and a USB CDC (communications device class) device. To change keybinds, you should connect to this CDC device, this can be done with any serial monitor. Examples of serial monitors are: The Arduino serial monitor (might be the easiest), Picocom (terminal based), Tera Term (if on windows). The terminal should show instructions on how to change the keybinds.

4. Following the instructions, hit the area of the drum, or button you want to rebind.

5. Type the name of the key you want to rebind it to, valid options are as follows:\
A\
B\
C\
D\
E\
F\
G\
H\
I\
J\
K\
L\
M\
N\
O\
P\
Q\
R\
S\
T\
U\
V\
W\
X\
Y\
Z\
1\
2\
3\
4\
5\
6\
7\
8\
9\
0\
ENTER\
ESCAPE\
BACKSPACE\
TAB\
SPACE\
MINUS\
EQUAL\
BRACKET\_LEFT\
BRACKET\_RIGHT\
BACKSLASH\
EUROPE\_1\
SEMICOLON\
APOSTROPHE\
GRAVE\
COMMA\
PERIOD\
SLASH\
CAPS\_LOCK\
F1\
F2\
F3\
F4\
F5\
F6\
F7\
F8\
F9\
F10\
F11\
F12\
PRINT\_SCREEN\
SCROLL\_LOCK\
PAUSE\
INSERT\
HOME\
PAGE\_UP\
DELETE\
END\
PAGE\_DOWN\
ARROW\_RIGHT\
ARROW\_LEFT\
ARROW\_DOWN\
ARROW\_UP\
NUM\_LOCK\
KEYPAD\_DIVIDE\
KEYPAD\_MULTIPLY\
KEYPAD\_SUBTRACT\
KEYPAD\_ADD\
KEYPAD\_ENTER\
KEYPAD\_1\
KEYPAD\_2\
KEYPAD\_3\
KEYPAD\_4\
KEYPAD\_5\
KEYPAD\_6\
KEYPAD\_7\
KEYPAD\_8\
KEYPAD\_9\
KEYPAD\_0\
KEYPAD\_DECIMAL\
EUROPE\_2\
APPLICATION\
POWER\
KEYPAD\_EQUAL\
F13\
F14\
F15\
F16\
F17\
F18\
F19\
F20\
F21\
F22\
F23\
F24\
EXECUTE\
HELP\
MENU\
SELECT\
STOP\
AGAIN\
UNDO\
CUT\
COPY\
PASTE\
FIND\
MUTE\
VOLUME\_UP\
VOLUME\_DOWN\
LOCKING\_CAPS\_LOCK\
LOCKING\_NUM\_LOCK\
LOCKING\_SCROLL\_LOCK\
KEYPAD\_COMMA\
KEYPAD\_EQUAL\_SIGN\
KANJI1\
KANJI2\
KANJI3\
KANJI4\
KANJI5\
KANJI6\
KANJI7\
KANJI8\
KANJI9\
LANG1\
LANG2\
LANG3\
LANG4\
LANG5\
LANG6\
LANG7\
LANG8\
LANG9\
ALTERNATE\_ERASE\
SYSREQ\_ATTENTION\
CANCEL\
CLEAR\
PRIOR\
RETURN\
SEPARATOR\
OUT\
OPER\
CLEAR\_AGAIN\
CRSEL\_PROPS\
EXSEL
