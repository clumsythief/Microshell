
# Microshell 💻
This is a simple project created for my Operating Systems class at Adam Mickiewicz University.

## Running the program
To use this program in a Linux system via terminal, follow these steps:
1. Download this project.
2. Open the Terminal on your computer and navigate to the folder that contains the microshell.c file.
3. Compile the program using this command: `gcc microshell.c -o microshell`.
4. Now you can run the program using the following command: `./microshell`.

## What does it do?
This program has several functionalities. You can use the `help` command while running the program to see all of them (available only in Polish).
- `help` will show you all possible commands
- `exit` will stop the program
- `cd [directory_name]` will change directory, there are also some other options you can write instead of `[direcroty_name]`:
    - `.` will change it to the current directory
    - `..` will send you to the parent directory
    - `~` will send you to the home directory
    - `-` will send you to the previous directory
- `mkdir [directory_name]` will create a new directory. This command can also create up to 9 directories at a time.
    - `[directory1_name]/[directory2_name]` will create a new directory and a sub-directory inside of it. You can create up to 4 directories at a time.
