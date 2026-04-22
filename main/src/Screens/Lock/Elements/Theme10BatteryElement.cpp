#include "Theme10BatteryElement.h"
#include "ZareenConfig.h"
#include "Util/Services.h"
#include "Services/Time.h"

// Dim a color to a fraction of its brightness
static lv_color_t dimColor(lv_color_t c, uint8_t factor){
	return lv_color_make(
		(lv_color_to32(c) >> 16 & 0xFF) * factor / 255,
		(lv_color_to32(c) >>  8 & 0xFF) * factor / 255,
		(lv_color_to32(c) >>  0 & 0xFF) * factor / 255
	);
}

Theme10BatteryElement::Theme10BatteryElement(lv_obj_t* parent) : BatteryElement(parent){
	auto* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){ return; }

	lv_obj_set_size(*this, ZareenCfg::containerW, ZareenCfg::containerH);
	lv_obj_set_style_bg_opa(*this, LV_OPA_0, 0);
	lv_obj_set_style_border_width(*this, 0, 0);
	lv_obj_set_style_pad_all(*this, 0, 0);

	// --- Year (Earth Orbit) ---
	yearLabel = lv_label_create(*this);
	lv_label_set_text(yearLabel, ZareenCfg::yearLabel);
	lv_obj_set_style_text_color(yearLabel, ZareenCfg::yearLabelColor, 0);
	lv_obj_set_pos(yearLabel, ZareenCfg::yearLabelX, ZareenCfg::yearLabelY);

	buildSegmentBar(yearBar, *this,
		ZareenCfg::yearBarX, ZareenCfg::yearBarY,
		ZareenCfg::yearSegments,
		ZareenCfg::yearBarColor,
		dimColor(ZareenCfg::yearBarColor, 80));

	// --- Month (Moon Orbit) ---
	monthLabel = lv_label_create(*this);
	lv_label_set_text(monthLabel, ZareenCfg::monthLabel);
	lv_obj_set_style_text_color(monthLabel, ZareenCfg::monthLabelColor, 0);
	lv_obj_set_pos(monthLabel, ZareenCfg::monthLabelX, ZareenCfg::monthLabelY);

	buildSegmentBar(monthBar, *this,
		ZareenCfg::monthBarX, ZareenCfg::monthBarY,
		ZareenCfg::monthSegments,
		ZareenCfg::monthBarColor,
		dimColor(ZareenCfg::monthBarColor, 80));

	// --- Day (Planetary Rotation) ---
	dayLabel = lv_label_create(*this);
	lv_label_set_text(dayLabel, ZareenCfg::dayLabel);
	lv_obj_set_style_text_color(dayLabel, ZareenCfg::dayLabelColor, 0);
	lv_obj_set_pos(dayLabel, ZareenCfg::dayLabelX, ZareenCfg::dayLabelY);

	buildSegmentBar(dayBar, *this,
		ZareenCfg::dayBarX, ZareenCfg::dayBarY,
		ZareenCfg::daySegments,
		ZareenCfg::dayBarColor,
		dimColor(ZareenCfg::dayBarColor, 80));

	// Battery icon (hidden, needed for base class)
	batteryIcon = lv_label_create(*this);
	lv_obj_add_flag(batteryIcon, LV_OBJ_FLAG_HIDDEN);

	updateProgressBars();
	set(getLevel());
}

void Theme10BatteryElement::buildSegmentBar(SegmentBar& bar, lv_obj_t* parent,
											int x, int y, int count,
											lv_color_t activeColor, lv_color_t dColor){
	bar.activeColor = activeColor;
	bar.dimColor    = dColor;
	bar.segments.reserve(count);

	for(int i = 0; i < count; i++){
		lv_obj_t* seg = lv_obj_create(parent);
		lv_obj_set_size(seg, ZareenCfg::segmentW, ZareenCfg::segmentH);
		lv_obj_set_pos(seg, x + i * (ZareenCfg::segmentW + ZareenCfg::segmentGap), y);
		lv_obj_set_style_radius(seg, 1, 0);
		lv_obj_set_style_border_width(seg, 0, 0);
		lv_obj_set_style_pad_all(seg, 0, 0);
		lv_obj_set_style_bg_opa(seg, LV_OPA_COVER, 0);
		lv_obj_set_style_bg_color(seg, dColor, 0);
		bar.segments.push_back(seg);
	}
}

void Theme10BatteryElement::updateSegmentBar(SegmentBar& bar, float progress){
	int lit = (int)(progress * bar.segments.size());
	for(int i = 0; i < (int)bar.segments.size(); i++){
		lv_obj_set_style_bg_color(bar.segments[i],
			i < lit ? bar.activeColor : bar.dimColor, 0);
	}
}

void Theme10BatteryElement::loop(){
	BatteryElement::loop();
	updateProgressBars();
}

void Theme10BatteryElement::updateProgressBars(){
	updateSegmentBar(yearBar,  getYearProgress());
	updateSegmentBar(monthBar, getMonthProgress());
	updateSegmentBar(dayBar,   getDayProgress());
}

float Theme10BatteryElement::getDayProgress() const {
	const Time* t = (Time*) Services.get(Service::Time);
	if(!t) return 0.0f;
	const tm tm = t->getTime();
	return (tm.tm_hour * 60 + tm.tm_min) / 1440.0f;
}

float Theme10BatteryElement::getMonthProgress() const {
	const Time* t = (Time*) Services.get(Service::Time);
	if(!t) return 0.0f;
	const tm tm = t->getTime();
	return (float)(tm.tm_mday - 1) / (float)getDaysInMonth(tm.tm_mon, tm.tm_year + 1900);
}

float Theme10BatteryElement::getYearProgress() const {
	const Time* t = (Time*) Services.get(Service::Time);
	if(!t) return 0.0f;
	const tm tm = t->getTime();
	return tm.tm_yday / 365.0f;
}

int Theme10BatteryElement::getDaysInMonth(int month, int year) const {
	static const int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if(month == 1){
		bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		return leap ? 29 : 28;
	}
	return days[month];
}

void Theme10BatteryElement::updateChargingVisuals(){
	lv_label_set_text(batteryIcon, "");
}

void Theme10BatteryElement::updateLevelVisuals(){
	lv_label_set_text(batteryIcon, "");
}
