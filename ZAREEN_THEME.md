# Zareen Theme

**Zareen** is a custom lock screen theme for the Artemis watch. It has a space/night-sky aesthetic with a star field background and three progress bars tracking astronomical cycles — inspired by the [Strange Planet](https://www.nathanwpyle.art/) webcomic's literal, technical take on everyday things.

---

## Layout

```
┌─────────────────────────────────┐
│ 21/04/2026          [battery]   │  ← date (top-left, gold)  battery (top-right, gold)
│                                 │
│          10:24                  │  ← clock (centered)
│                                 │
├─────────────────────────────────┤  ← separator
│ STAR ORBIT                      │
│ [██████░░░░]                    │  ← year bar  (50% width, gold)
│ LUNAR PASSAGE                   │
│ [████░░░░░░]                    │  ← month bar (50% width, silver)
│ ORB ROTATION                    │
│ [████████████░░░░]              │  ← day bar   (75% width, blue)
│                                 │
│ ════════ SLIDER ════════        │  ← unlock slider
└─────────────────────────────────┘
```

---

## Progress Bars

Each bar is made of individual lit/dim block segments — like a sci-fi level meter.

| Bar | Label | Cycle | Width | Color | Segments |
|-----|-------|-------|-------|-------|----------|
| Year | `STAR ORBIT` | Earth's orbit around the sun (365 days) | 50% | Gold | 12 (one per month) |
| Month | `LUNAR PASSAGE` | Moon's orbit around Earth (~30 days) | 50% | Silver | 10 |
| Day | `ORB ROTATION` | Earth's rotation (24 hours) | 75% | Blue | 16 |

---

## Configuration

Everything is controlled from a single file:

**`main/src/Screens/Lock/Elements/ZareenConfig.h`**

Key settings:

```cpp
// Colors
inline constexpr lv_color_t yearBarColor  = LV_COLOR_MAKE(255, 200, 100);  // gold
inline constexpr lv_color_t monthBarColor = LV_COLOR_MAKE(180, 180, 220);  // silver
inline constexpr lv_color_t dayBarColor   = LV_COLOR_MAKE(80,  150, 255);  // blue

// Labels
inline constexpr const char* yearLabel  = "STAR ORBIT";
inline constexpr const char* monthLabel = "LUNAR PASSAGE";
inline constexpr const char* dayLabel   = "ORB ROTATION";

// Segments per bar
inline constexpr int yearSegments  = 10;
inline constexpr int monthSegments = 10;
inline constexpr int daySegments   = 16;

// Segment geometry
inline constexpr int segmentW   = 4;  // px wide
inline constexpr int segmentH   = 6;  // px tall
inline constexpr int segmentGap = 2;  // px between segments

// Positions (center-relative for clock/date, absolute for bars)
inline constexpr int clockX = 0;      // centered
inline constexpr int clockY = -29;
inline constexpr int dateX  = 6;      // top-left
inline constexpr int dateY  = 6;
```

After editing, rebuild and flash:
```shell
make build && make flash PORT=/dev/ttyACM0
```

---

## Assets

Theme assets live in `spiffs_image/theme10/`:

| Directory | Contents |
|-----------|----------|
| `lock_screen/` | Background image (`bg.bin`) |
| `clock/` | Digit images `0-9.bin`, `colon.bin` (from Default theme) |
| `icon/` | Notification icons (from Duotone theme) |
| `small/` | Small notification icons |
| `menu/` | Menu backgrounds and icons |

### Replacing the background

1. Create a **128×128 PNG** (night sky recommended)
2. Convert and flash:
```shell
/path/to/python bin_to_png.py   # preview existing
# Use LVGL image converter: https://lvgl.io/tools/imageconverter
# Settings: Indexed 4-bit, Binary output
```
Or use the included converter script:
```shell
# The script also converts TO bin — see bin_to_png.py source
```

---

## Implementation

| File | Role |
|------|------|
| `ZareenConfig.h` | All configuration constants |
| `Theme10BatteryElement.h/cpp` | Custom element rendering the 3 segment bars |
| `LockSkin.cpp` | Wires the theme into the lock screen (special alignment, battery recolor) |
| `Settings/Settings.h` | Theme10 struct values (all sourced from ZareenConfig.h) |
| `Filepaths.hpp` | Asset paths for theme10 |

The theme is registered as **Theme10** in the firmware and is set as the **default theme**.
It appears as **"Zareen"** in the Settings → Theme picker.
