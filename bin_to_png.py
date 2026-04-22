#!/usr/bin/env python3
"""Convert LVGL INDEXED_4BIT .bin files to PNG"""

import struct
import sys
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    print("Installing Pillow...")
    import subprocess
    subprocess.run([sys.executable, "-m", "pip", "install", "Pillow"], check=True)
    from PIL import Image

def bin_to_png(bin_path, png_path=None):
    data = open(bin_path, 'rb').read()

    hdr  = struct.unpack_from('<I', data, 0)[0]
    cf   = (hdr >> 0) & 0x1F
    w    = (hdr >> 10) & 0x7FF
    h    = (hdr >> 21) & 0x7FF

    # Parse 16-color BGRA palette
    palette_raw = data[4:4+64]
    palette = []
    for i in range(16):
        b, g, r, a = palette_raw[i*4], palette_raw[i*4+1], palette_raw[i*4+2], palette_raw[i*4+3]
        palette.append((r, g, b, a))

    # Unpack 4-bit pixel indices (2 pixels per byte, high nibble first)
    pixel_data = data[4+64:]
    img = Image.new('RGBA', (w, h))
    pixels = []
    for byte in pixel_data:
        hi = (byte >> 4) & 0x0F
        lo = (byte >> 0) & 0x0F
        pixels.append(palette[hi])
        pixels.append(palette[lo])

    img.putdata(pixels[:w*h])

    if png_path is None:
        png_path = str(bin_path).replace('.bin', '.png')

    img.save(png_path)
    print(f"Saved: {png_path}  ({w}x{h})")
    return png_path

if __name__ == "__main__":
    paths = sys.argv[1:] if len(sys.argv) > 1 else [
        "spiffs_image/theme2/lock_screen/bg.bin",
        "spiffs_image/theme10/lock_screen/bg.bin",
    ]
    for p in paths:
        bin_to_png(p)
