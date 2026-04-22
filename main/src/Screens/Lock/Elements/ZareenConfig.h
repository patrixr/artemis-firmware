#pragma once
#include <lvgl.h>

// ============================================================
//  Zareen Theme Configuration
//  Edit this file to change the theme layout and colors.
//  Screen size: 128 x 128 pixels
//  Coordinate system for clock / date / phone:
//    center-relative  (positive = right / down)
//  Coordinate system for bars:
//    absolute from top-left corner
// ============================================================

namespace ZareenCfg {

	// ----------------------------------------------------------
	//  Colors
	// ----------------------------------------------------------
	inline constexpr lv_color_t bgColor          = LV_COLOR_MAKE(5,   10,  30);   // dark space blue
	inline constexpr lv_color_t textColor        = LV_COLOR_MAKE(255, 255, 255);  // white
	inline constexpr lv_color_t dateColor        = LV_COLOR_MAKE(255, 200, 100);  // gold
	inline constexpr lv_color_t primaryColor     = LV_COLOR_MAKE(15,  30,  80);   // night-sky blue (accent/label bg)
	inline constexpr lv_color_t secondaryColor   = LV_COLOR_MAKE(255, 255, 255);  // white text on primary bg
	inline constexpr lv_color_t highlightColor   = LV_COLOR_MAKE(60,  100, 200);  // mid blue (borders/labels)
	inline constexpr lv_color_t statusBarColor   = LV_COLOR_MAKE(15,  30,  80);   // deep night-sky blue

	// ----------------------------------------------------------
	//  Clock  (center-relative)
	// ----------------------------------------------------------
	inline constexpr int clockX       = 0;    // centered
	inline constexpr int clockY       = -29;  // 5% lower
	inline constexpr bool clockVertical = false;
	inline constexpr int clockPadding = 0;

	// Date: TOP_LEFT aligned (absolute px from top-left corner)
	inline constexpr int dateX = 6;   // 5% left padding
	inline constexpr int dateY = 6;   // slightly lower to align with battery

	// Small battery: TOP_RIGHT aligned (offset from top-right corner)
	inline constexpr int smallBatteryX = -6;  // 5% right padding
	inline constexpr int smallBatteryY = 4;

	// ----------------------------------------------------------
	//  Phone icon  (center-relative)
	// ----------------------------------------------------------
	inline constexpr int  phoneX       = 56;
	inline constexpr int  phoneY       = -58;
	inline constexpr bool phoneSpecial = false;

	// ----------------------------------------------------------
	//  Unlock slider
	// ----------------------------------------------------------
	inline constexpr int  sliderY        = 111;
	inline constexpr int  sliderStart    = 6;
	inline constexpr int  sliderEnd      = 122;
	inline constexpr int  sliderBarY     = 3;
	inline constexpr bool sliderNeverHide = false;

	// ----------------------------------------------------------
	//  Notifications
	// ----------------------------------------------------------
	inline constexpr int notifX        = 0;
	inline constexpr int notifY        = 90;
	inline constexpr int notifW        = 128;
	inline constexpr int notifH        = 10;
	inline constexpr int notifGap      = 2;
	inline constexpr int notifMaxCount = 8;

	// ----------------------------------------------------------
	//  Progress bars container  (absolute position)
	// ----------------------------------------------------------
	inline constexpr int containerX = 6;
	inline constexpr int containerY = 65;  // was 59, +6px (5%)
	inline constexpr int containerW = 122;  // 128 - 6
	inline constexpr int containerH = 60;

	// ------ Segment bar geometry --------------------------------
	inline constexpr int segmentW     = 4;   // width of each block
	inline constexpr int segmentH     = 6;   // height of each block
	inline constexpr int segmentGap   = 2;   // gap between blocks
	inline constexpr int yearSegments  = 10; // 50% width
	inline constexpr int monthSegments = 10; // 50% width
	inline constexpr int daySegments   = 16; // 75% width
	inline constexpr const char* yearLabel     = "STAR ORBIT";
	inline constexpr int         yearLabelX    = 0;
	inline constexpr int         yearLabelY    = 0;
	inline constexpr lv_color_t  yearLabelColor = LV_COLOR_MAKE(255, 255, 255);
	inline constexpr int         yearBarX      = 0;
	inline constexpr int         yearBarY      = 11;  // labelY(0) + font(8) + gap(3)
	inline constexpr int         yearBarW      = 64;   // 50 % of screen
	inline constexpr int         yearBarH      = 8;
	inline constexpr lv_color_t  yearBarColor  = LV_COLOR_MAKE(255, 200, 100);  // gold
	inline constexpr lv_color_t  yearBarBg     = LV_COLOR_MAKE(40,  40,  40);

	// ------ Month bar (Moon Orbit) ----------------------------
	inline constexpr const char* monthLabel      = "LUNAR PASSAGE";
	inline constexpr int         monthLabelX     = 0;
	inline constexpr int         monthLabelY     = 20;
	inline constexpr lv_color_t  monthLabelColor = LV_COLOR_MAKE(255, 255, 255);
	inline constexpr int         monthBarX       = 0;
	inline constexpr int         monthBarY       = 31;  // labelY(20) + font(8) + gap(3)
	inline constexpr int         monthBarW       = 64;   // 50 % of screen
	inline constexpr int         monthBarH       = 8;
	inline constexpr lv_color_t  monthBarColor   = LV_COLOR_MAKE(180, 180, 220);  // silver
	inline constexpr lv_color_t  monthBarBg      = LV_COLOR_MAKE(40,  40,  40);

	// ------ Day bar (Planetary Rotation) ----------------------
	inline constexpr const char* dayLabel      = "ORB ROTATION";
	inline constexpr int         dayLabelX     = 0;
	inline constexpr int         dayLabelY     = 40;
	inline constexpr lv_color_t  dayLabelColor = LV_COLOR_MAKE(255, 255, 255);
	inline constexpr int         dayBarX       = 0;
	inline constexpr int         dayBarY       = 51;  // labelY(40) + font(8) + gap(3)
	inline constexpr int         dayBarW       = 90;   // 75% minus shift offset
	inline constexpr int         dayBarH       = 8;
	inline constexpr lv_color_t  dayBarColor   = LV_COLOR_MAKE(80,  150, 255);  // blue
	inline constexpr lv_color_t  dayBarBg      = LV_COLOR_MAKE(40,  40,  40);

} // namespace ZareenCfg
