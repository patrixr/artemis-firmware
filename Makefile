PORT ?= /dev/ttyACM0
ESP_IDF_DIR := $(CURDIR)/esp-idf

.PHONY: prepare submodules patch patch-idf patch-jpegdec patch-lovyangfx build flash merge restore clean

prepare: submodules
	@if [ ! -d "$(ESP_IDF_DIR)" ]; then \
		git clone --depth 1 --recurse-submodules --shallow-submodules --branch v5.1 https://github.com/espressif/esp-idf.git $(ESP_IDF_DIR); \
		$(ESP_IDF_DIR)/install.sh; \
	else \
		echo "esp-idf already cloned."; \
	fi
	@cd $(ESP_IDF_DIR) && git apply $(CURDIR)/ESP-IDF.patch 2>/dev/null || echo "ESP-IDF patch already applied or skipped."
	@cd components/JPEGDEC && git apply ../../JPEGDEC.patch 2>/dev/null || echo "JPEGDEC patch already applied or skipped."
	@cd components/LovyanGFX && git apply ../../LovyanGFX.patch 2>/dev/null || echo "LovyanGFX patch already applied or skipped."

submodules:
	git submodule update --init --recursive -- components/JPEGDEC components/LovyanGFX main/lib/mjson main/lib/glm components/Perse-Common
	@if [ ! -d "components/lvgl/.git" ]; then \
		rm -rf components/lvgl && mkdir -p components/lvgl && \
		cd components/lvgl && git init && \
		git remote add origin https://github.com/lvgl/lvgl.git && \
		git fetch --depth=1 origin e6d7be00bfa5e1df450c7b713003a9effa03c614 && \
		git checkout FETCH_HEAD; \
	else \
		echo "lvgl already cloned."; \
	fi

patch-idf:
	cd $(ESP_IDF_DIR) && git apply $(CURDIR)/ESP-IDF.patch

patch-jpegdec:
	cd components/JPEGDEC && git apply ../../JPEGDEC.patch

patch-lovyangfx:
	cd components/LovyanGFX && git apply ../../LovyanGFX.patch

patch: patch-jpegdec patch-lovyangfx

build:
	@. $(ESP_IDF_DIR)/export.sh && idf.py build

flash:
	@. $(ESP_IDF_DIR)/export.sh && idf.py -p $(PORT) flash

flash-monitor:
	@. $(ESP_IDF_DIR)/export.sh && idf.py -p $(PORT) flash monitor

monitor:
	@. $(ESP_IDF_DIR)/export.sh && idf.py -p $(PORT) monitor

merge:
	@. $(ESP_IDF_DIR)/export.sh && cd build && esptool --chip esp32s3 merge_bin --fill-flash-size 4MB -o ../Artemis.bin \
		--flash_mode dio --flash_freq 80m --flash_size 4MB \
		0x0 bootloader/bootloader.bin \
		0x10000 Artemis-Firmware.bin \
		0x8000 partition_table/partition-table.bin \
		0x2f6000 storage.bin

restore:
	@. $(ESP_IDF_DIR)/export.sh && esptool -c esp32s3 -b 921600 -p $(PORT) write_flash 0 Artemis.bin

clean:
	idf.py fullclean
