# Zareen Theme Assets

**Theme Concept**: Space/Night Sky theme with cosmic colors and astronomical progress bars

## Color Scheme
- Primary: Deep space blue (#6496FF)
- Secondary: Light cosmic blue (#C8C8FF)
- Highlight: Star gold (#FFC864)
- Background: Deep space (#0A0A1E)
- Date: Subtle gray-blue (#B4B4DC)

## Required Assets

### Lock Screen (`lock_screen/`)
- `bg.bin` - Night sky background with stars (128x128)
- `phone.bin` - Phone connected icon (space-themed)
- `phoneDc.bin` - Phone disconnected icon

### Clock Digits (`clock/`)
- `0.bin` through `9.bin` - Digital clock numbers (space/futuristic style)
- `colon.bin` - Colon separator (:)
- `space.bin` - Space character for padding

### Notification Icons (`icon/` - Large, `small/` - Small versions)

#### App Icons
- `app_inst.bin` - Instagram
- `app_mess.bin` - Messenger
- `app_sms.bin` - SMS
- `app_snap.bin` - Snapchat
- `app_tiktok.bin` - TikTok
- `app_wapp.bin` - WhatsApp

#### Call Icons
- `call_in.bin` - Incoming call
- `call_miss.bin` - Missed call
- `call_out.bin` - Outgoing call

#### Category Icons
- `cat_email.bin` - Email
- `cat_entert.bin` - Entertainment
- `cat_fin.bin` - Finance
- `cat_health.bin` - Health
- `cat_loc.bin` - Location
- `cat_news.bin` - News
- `cat_other.bin` - Other
- `cat_sched.bin` - Schedule
- `cat_soc.bin` - Social

#### Lock Icons
- `lock_closed.bin` - Locked state
- `lock_open.bin` - Unlocked state

### Menu (`menu/`)
- `bg.bin` - Menu background
- `batteryEmpty.bin` - Empty battery indicator
- `batteryLow.bin` - Low battery indicator
- `batteryMid.bin` - Medium battery indicator
- `batteryFull.bin` - Full battery indicator
- `phone.bin` - Phone connected menu icon
- `phoneDc.bin` - Phone disconnected menu icon
- `connection.bin` - Connection settings icon
- `find.bin` - Find phone icon
- `level.bin` - Level app icon
- `settings.bin` - Settings icon
- `theremin.bin` - Theremin app icon
- `lunar.bin` - Lunar Lander game icon
- `rover.bin` - Mars Rover game icon
- `notif.bin` - Notifications icon

## Theme Features

The Zareen theme includes three unique progress bars on the lock screen:
1. **Day Bar** (Blue) - Shows planetary rotation (24-hour cycle)
2. **Month Bar** (Silver) - Shows moon orbit (monthly cycle)
3. **Year Bar** (Gold) - Shows planetary orbit (yearly cycle)

Time is displayed in the top-right corner, with a small battery indicator near the progress bars.

## Asset Specifications

- Format: `.bin` files (LVGL binary format)
- Screen resolution: 128x128 pixels
- Recommended tool: LVGL Image Converter
- Color depth: Match device specifications

## Creating Assets

1. Design your graphics in your preferred editor
2. Convert to LVGL format using: https://lvgl.io/tools/imageconverter
3. Save as `.bin` files with the names specified above
4. Place in the appropriate subdirectory

## Notes

- The custom battery element (Theme10BatteryElement) renders the three progress bars programmatically
- This theme does NOT use the standard battery images (b1.bin, b2.bin, etc.)
- Focus on creating a cohesive space/astronomy aesthetic across all icons
