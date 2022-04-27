// This example is not self-contained.
// It requires usage of the example driver specific to your platform.
// See the HAL documentation.

#include "src/bindings/hal_common.h"
#include "src/bindings/bricklet_distance_us_v2.h"

void check(int rc, const char *msg);
void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);

// Callback function for distance callback
static void distance_handler(TF_DistanceUSV2 *device, uint16_t distance,
                             void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Distance: %d 1/%d cm\n", distance, 10);
}

static TF_DistanceUSV2 dus;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_distance_us_v2_create(&dus, NULL, hal), "create device object");

	// Register distance callback to function distance_handler
	tf_distance_us_v2_register_distance_callback(&dus,
	                                             distance_handler,
	                                             NULL);

	// Configure threshold for distance "greater than 100 cm"
	// with a debounce period of 0.1s (100ms)
	tf_distance_us_v2_set_distance_callback_configuration(&dus, 100, false, '>', 100*10, 0);
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
