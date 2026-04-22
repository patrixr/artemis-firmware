#ifndef ARTEMIS_FIRMWARE_THEME10BATTERYELEMENT_H
#define ARTEMIS_FIRMWARE_THEME10BATTERYELEMENT_H

#include "UIElements/BatteryElement.h"
#include "Services/Time.h"
#include <vector>

class Theme10BatteryElement : public BatteryElement {
public:
	explicit Theme10BatteryElement(lv_obj_t* parent);
	virtual ~Theme10BatteryElement() override = default;

	void loop() override;

protected:
	void updateChargingVisuals() override;
	void updateLevelVisuals() override;

private:
	struct SegmentBar {
		std::vector<lv_obj_t*> segments;
		lv_color_t activeColor;
		lv_color_t dimColor;
	};

	SegmentBar yearBar;
	SegmentBar monthBar;
	SegmentBar dayBar;

	lv_obj_t* yearLabel;
	lv_obj_t* monthLabel;
	lv_obj_t* dayLabel;
	lv_obj_t* batteryIcon;

	void buildSegmentBar(SegmentBar& bar, lv_obj_t* parent,
						 int x, int y, int count,
						 lv_color_t activeColor, lv_color_t dimColor);
	void updateSegmentBar(SegmentBar& bar, float progress);

	void updateProgressBars();
	float getDayProgress() const;
	float getMonthProgress() const;
	float getYearProgress() const;
	int   getDaysInMonth(int month, int year) const;
};

#endif //ARTEMIS_FIRMWARE_THEME10BATTERYELEMENT_H
