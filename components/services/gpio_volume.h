#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	GPIO_VOLUME_MODE_LEDBAR,
	GPIO_VOLUME_MODE_BINARY,
	GPIO_VOLUME_MODE_LATCHING
} gpio_volume_mode_t;

typedef struct {
	gpio_volume_mode_t mode;
	int width;          /* Number of GPIO bits used */
	int lsb0;           /* Start GPIO for primary bank */
	int lsb0_level;     /* Active level for lsb0 (0 or 1) */
	int lsb1;           /* Start GPIO for secondary bank (Latching Mode A) */
	int lsb1_level;     /* Active level for lsb1 */
	int high0;          /* Direction/Rail GPIO 0 (Latching Mode B) */
	int high0_level;    /* Active level for high0 */
	int high1;          /* Direction/Rail GPIO 1 (Latching Mode B) */
	int high1_level;    /* Active level for high1 */
	int time_ms;        /* Pulse duration for latching relays */
	bool dacmax;        /* Fixed DAC max setting */
	bool visumax;       /* Fixed visualization max setting */
	bool loud;          /* Normal or inverted logic for binary mode */
} gpio_volume_cfg_t;

typedef struct {
	bool active; 		// true = gpio_volume is configured
	bool dac_fixed;		// true = bypass digital gain, use external volume control
	bool visu_fixed;	// true = visualization at max volume, false = follows volume setting
} gpio_max_mode_t;

bool gpio_volume_init(const char *cfg);
void gpio_volume_apply_startup_volume(unsigned gain);
void gpio_volume_update(unsigned gain);
gpio_max_mode_t gpio_volume_get_mode(void);