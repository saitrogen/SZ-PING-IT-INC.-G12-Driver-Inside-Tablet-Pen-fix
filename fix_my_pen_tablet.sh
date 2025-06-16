#!/bin/bash

# --- The Interactive Tablet Fixer (User-Guided) ---

# Step 1: Run the unlocker program to initialize the tablet hardware.
echo "Unlocking tablet..."
sudo unlock_tablet

# Step 2: Prompt the user to perform the manual "poke".
# The script will PAUSE here until you click "OK".
zenity --info \
       --title="Action Required: Wake Up Tablet" \
       --text="<b>The tablet is unlocked.</b>\n\nPlease move your pen on the tablet surface now to wake it up.\n\nClick OK after you have moved the pen." \
       --width=300

# The script continues only after you click OK.

# Step 3: Now that the tablet is awake, find its ID.
# We will use the robust method with a hard-coded fallback.
TABLET_ID=$(xinput list --id-only "SZ PING-IT INC.  [G12 ] Driver Inside Tablet Pen (0)")
if [ -z "$TABLET_ID" ]; then
    echo "Could not find tablet by name. Falling back to static ID 23."
    TABLET_ID=23
fi

# Step 4: Let the user choose the monitor graphically.
#CHOSEN_MONITOR=$(zenity --list --title="Select a Monitor" --text="Choose a monitor for your tablet:" --column="Monitor" $(xrandr | grep " connected" | cut -d ' ' -f1))

# Exit if the user cancelled the monitor selection.
#if [ -z "$CHOSEN_MONITOR" ]; then
#   echo "No monitor selected. Exiting."
#    exit 0
#fi

# Step 5: Apply the two known fixes in the correct order.
echo "Applying final configuration..."
xinput set-prop 23 "Coordinate Transformation Matrix" 1 0 0 0 1 0 0 0 1
#xinput map-to-output 23 "$CHOSEN_MONITOR"

echo "Configuration complete. Your tablet is ready to use!"
