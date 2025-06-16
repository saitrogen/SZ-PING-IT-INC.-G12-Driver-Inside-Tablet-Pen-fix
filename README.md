# Linux Fix for SZ PING-IT G12 / Bestor G12 Pen Tablet

A complete solution to enable the full resolution and fix mapping issues for the `VID:08f2 PID:6811` series of graphics tablets on Linux (specifically for Xorg sessions).
This repository contains a full toolkit to make this off-brand tablet work perfectly on Linux.

![bestor pen tab](https://github.com/user-attachments/assets/da1718f8-c37c-418d-9a69-8ed7631d9015)

## The Problem
This tablet has two major issues on Linux out-of-the-box:
1.  **Shrunken Hardware Area:** It wakes up in a low-resolution "sleep mode," making only a small part of the tablet surface usable.
2.  **Shrunken Screen Area:** After fixing the hardware, the Linux display driver incorrectly tries to preserve the aspect ratio, confining the cursor to a portion of the screen.

This fix solves both problems permanently and automatically.

## The Solution
This repository provides two key components:
1.  **`unlock_tablet`**: A small C program that sends a "secret handshake" of commands to the tablet, waking it up into its full, high-resolution mode. This solves the hardware problem. u must verify the the vender id
2.  **`fix_my_pen_tablet.sh`**: An interactive shell script that automates the entire process:
    *   It runs the `unlock_tablet` program.
    *   It prompts you to "wake up" the software driver by moving the pen.
    *   It applies the final configuration fix to give you full access to your screen.
3.  if the `id` and all other variables `vender id ` & `PID ` are same the just down load the file and run .

     if u are strugling just send this to any llm :) he will guide u 
---

## Step 1: Install Dependencies
First, you need to install the tools required to build and run the fix. Open a terminal and run this command:
```bash
sudo apt update && sudo apt install build-essential libusb-1.0-0-dev zenity
```
*   `build-essential` & `libusb-1.0-0-dev`: Needed to compile the C program.
*   `zenity`: Needed to create the pop-up windows for the script.

---

## Step 2: Compile the Unlock Program
This turns the `unlock_tablet.c` source code into an executable program.

In the repository folder, run:
```bash
gcc -o unlock_tablet unlock_tablet.c -lusb-1.0
```
You should now see a new `unlock_tablet` program in the folder.

---

## Step 3: Run the Automation Script
This script handles everything from here.

First, make the script executable:
```bash
chmod +x fix_my_pen_tablet.sh
```
Now, run the script to test it:
```bash
./fix_my_pen_tablet.sh
```
Follow the on-screen prompts. Your tablet should now be working perfectly for your current session!

---

## Step 4: Make the Fix Permanent (Run on Startup)
To make this happen every time you log in, we need to move the unlocker program and add the script to your startup applications.

1.  **Move the `unlock_tablet` Program:** This places it in a standard system location so the script can find it easily.
    ```bash
    sudo mv unlock_tablet /usr/local/bin/
    ```

2.  **Add to Startup Applications:**
    *   Search for and open the **"Startup Applications"** program on your system.
    *   Click **"Add"**.
    *   Fill in the fields:
        *   **Name:** `Pen Tablet Fix`
        *   **Command:** Click "Browse..." and select the `fix_my_pen_tablet.sh` file from this repository folder.
        *   **Comment:** `Initializes and maps my G12 pen tablet.`
    *   Click **"Add"**.

**You are done!** The next time you reboot, the script will run automatically and configure your tablet.

---

## Customization & Troubleshooting for Beginners
The script tries to be smart, but sometimes you need to check things manually. Here is how you can find the information yourself.

### How to Find Your Tablet's ID
Your system assigns a unique ID number to your tablet. To find it, run:
```bash
xinput list
```
The output will look something like this. You are looking for the `Pen` device.
```
⎡ Virtual core pointer                    	id=2	[master pointer  (3)]
⎜   ↳ Virtual core XTEST pointer              	id=4	[slave  pointer  (2)]
⎜   ↳ SynPS/2 Synaptics TouchPad              	id=15	[slave  pointer  (2)]
⎜   ↳ SZ PING-IT INC.  [G12 ] Driver Inside Tablet Mouse	id=22	[slave  pointer  (2)]
⎜   ↳ SZ PING-IT INC.  [G12 ] Driver Inside Tablet Pen (0)	id=23	[slave  pointer  (2)]  <---- This is the one! The ID is 23.
⎣ Virtual core keyboard                   	id=3	[master keyboard (2)]
    ↳ ... (other devices)
```
Our script automatically looks for this ID but uses `23` as a backup.

### How to Fix the Screen Area Manually
If the script ever fails, you can run the final configuration commands yourself. Using the ID you found above (e.g., `23`), run this command to fix the shrunken screen area:
```bash
xinput set-prop 23 "Coordinate Transformation Matrix" 1 0 0 0 1 0 0 0 1
```

### How to Map to a Specific Monitor Manually
If you want to lock the tablet to a specific monitor, first find your monitor's name:
```bash
xrandr | grep " connected"
```
This might output `VGA-1 connected...` or `HDMI-1 connected...`. The name is the first part (`VGA-1` or `HDMI-1`).

Then use this command, replacing `23` with your tablet ID and `VGA-1` with your monitor name:
```bash
xinput map-to-output 23 "VGA-1"
```

## The Full Story
Curious about how this solution was developed? We documented the entire debugging process, from reverse-engineering the hardware commands to solving software race conditions. You can read it here: **[The Story of the Fix (DEBUGGING.md)](DEBUGGING.md)**
