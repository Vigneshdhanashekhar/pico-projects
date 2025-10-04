#!/bin/bash

# Check if UF2 file was provided
if [ -z "$1" ]; then
    echo "Usage: ./upload_pico.sh <path_to_uf2_file>"
    echo "Example: ./upload_pico.sh build/blink.uf2"
    exit 1
fi

UF2_FILE="$1"

# Check if file exists
if [ ! -f "$UF2_FILE" ]; then
    echo "Error: File $UF2_FILE not found!"
    exit 1
fi

# Create mount point if it doesn't exist
sudo mkdir -p /mnt/pico

echo "Looking for Pico in BOOTSEL mode..."

# Try common drive letters
for DRIVE in E F D G H; do
    echo "Trying drive ${DRIVE}:..."
    
    # Attempt to mount
    if sudo mount -t drvfs ${DRIVE}: /mnt/pico 2>/dev/null; then
        # Check if it's actually the Pico
        if [ -f /mnt/pico/INFO_UF2.TXT ]; then
            echo "✓ Found Pico at ${DRIVE}:"
            echo "Copying $UF2_FILE to Pico..."
            
            cp "$UF2_FILE" /mnt/pico/
            
            if [ $? -eq 0 ]; then
                echo "✓ Upload successful!"
                echo "Pico will reboot automatically."
                sudo umount /mnt/pico
                exit 0
            else
                echo "✗ Copy failed!"
                sudo umount /mnt/pico
                exit 1
            fi
        else
            # Not the Pico, unmount and try next
            sudo umount /mnt/pico 2>/dev/null
        fi
    fi
done

echo "✗ Pico not found!"
echo ""
echo "Make sure:"
echo "1. Pico is connected via USB"
echo "2. You held BOOTSEL button while plugging it in"
echo "3. Windows shows it as RPI-RP2 drive"
exit 1
