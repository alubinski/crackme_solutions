Notes:

First I checked main file with commands file, nm, strings. I learned information about whether program is stripped, architecture, used symbols and std::inout strings used by program. Than i loaded program into IDA to look at assembler instrutions. Than based on them i created pseudocode found in file pseudo.c

Serial should be up to 20 alphanumerical characters.

In first check we test lenghth of serial.

In second check we calculate and test checksum. I am confused by bit structure returned by ___ctype_b_loc
According to other solutions:
    signs 0-9 are substracted by 0x30 so in checksum they have value 0-9
    signs A-Z are substracted by 0x37 so they are translated to value 10-n
    signs a-z arre firstly upscaled to A-Z than transclated similary
    than values are added and checked if sum is dividable by 7
But values used in ABD operations seem weird, if we want to check if char is numeric IN MY UNDERSTANDING we should do AND with 0x8 instead of 0x800
later we do AND with 0x400 but shouldn't it be 0x800 to check if is not alphanumeric?
Pseudocode seems to be correct based on assembler instructions shown by IDA and other solutions.

https://github.com/alubinski/crackme_solutions/blob/main/write_a_keygen/img1.png

In third check we test if serial is in blacklist[2] = {"ABC123", "DEF456"}

