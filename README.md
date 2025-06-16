# Linux Fix for SZ PING-IT G12 / Bestor G12 Pen Tablet
A complete solution to enable the full resolution and fix mapping issues for the `VID:08F2 PID:6811` series of graphics tablets on Linux (Xorg).

![Tablet Working](https://i.imgur.com/w9N3g3D.png) <!-- You can replace this with a screenshot of your working setup! -->

## The Problem
This tablet, when used on Linux, defaults to a low-resolution "sleep" mode. This results in two major issues:
1.  **Shrunken Active Area:** Only a small portion of the physical tablet surface is responsive.
2.  **Incorrect Screen Mapping:** When the shrunken area is fixed, the cursor is often confined to a portion of the screen due to faulty aspect ratio correction.

This fix solves both problems permanently.

## The Solution
This repository provides two key components:
1.  **`unlock_tablet`**: A small C program that sends a "secret handshake" of commands to the tablet, waking it up into its full, high-resolution mode.
2.  **`fix_my_pen_tablet.sh`**: An interactive shell script that automates the entire process: unlocking the tablet, prompting the user to wake it up, and applying the necessary configuration to fix the screen mapping.
[ make sure u change the **`id`** in the files ]

## Prerequisites
Before you begin, you need to install the necessary tools for compiling the C program and creating the pop-up windows. Open a terminal and run:
```bash
sudo apt update && sudo apt install build-essential libusb-1.0-0-dev zenity
```

## Installation & Usage (Quick Start)

**Step 1: Clone the Repository**
```bash
git clone https://github.com/your-username/SZ-PING-IT-INC.-G12-Driver-Inside-Tablet-Pen-fix.git
cd SZ-PING-IT-INC.-G12-Driver-Inside-Tablet-Pen-fix
```

**Step 2: Compile the Unlock Program**
Use the `gcc` compiler to turn the source code into an executable program.
```bash
gcc -o unlock_tablet unlock_tablet.c -lusb-1.0
```

**Step 3: Move the Program to a System Path**
This makes the `unlock_tablet` command available system-wide, just like a real command.
```bash
sudo mv unlock_tablet /usr/local/bin/
```

**Step 4: Make the Automation Script Executable**
```bash
chmod +x fix_my_pen_tablet.sh
```

**Step 5: Run the Fix!**
Execute the main script. It will guide you through the rest.
```bash
./fix_my_pen_tablet.sh
```
What will happen:
1. A terminal will ask for your password to run the unlocker.
2. A pop-up window will appear, telling you to move your pen on the tablet.
3. Move the pen, then click "OK".
4. The script will apply the fixes, and your tablet will be perfectly configured for your session!

## Making the Fix Permanent (Run on Startup)
To have this fix apply automatically every time you log in:

1.  Search for and open the **"Startup Applications"** program on your system.
2.  Click **"Add"**.
3.  Fill in the fields:
    *   **Name:** `Pen Tablet Fix`
    *   **Command:** Click "Browse..." and select the `fix_my_pen_tablet.sh` file from this repository folder.
    *   **Comment:** `Initializes and maps my G12 pen tablet.`
4.  Click **"Add"** and you're done!

## Having a Different Tablet?
This fix is specific to the `VID:08F2 PID:6811` tablet. However, the *method* can be adapted. To learn about the debugging journey and how this solution was created, please read our detailed guide: **[The Story of the Fix (DEBUGGING.md)](DEBUGGING.md)**.

## License
This project is licensed under the MIT License.
