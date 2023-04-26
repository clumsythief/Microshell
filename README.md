
# Microshell 💻
This is a simple project for my Operating Systems class at Adam Mickiewicz University.

## How to use it
You can use this program in Linux system via terminal. Here are the steps you need to do to run the program:  
- Download this project
- Open Terminal on your computer and go to the folder which contains file microshell.c 
- Compile the program using this command: `gcc microshell.c -o microshell`
- Now you can run the program using the following command: `./microshell`

## What does it do?
This program has few functionalities. You can use command `help` while running the program to see all of them (only available in polish).
- `help` will show you all possible commands
- `exit` will stop the program
- `cd [directory_name]` will change directory, there are also some other options you can write instead of `[direcroty_name]`:
    - `.` will change it to current directory
    - `..` will send you to parent directory
    - `~` will send you to home directory
    - `-` will send you to previous directory
- `mkdir [directory_name]` will make a new directory (this can also create up to 9 directories at a time).
    - `[directory1_name]/[directory2_name]` will create a new directory and a sub-directory inside of it (you can create up to 4 directories at a time).

