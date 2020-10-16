// This example is not self-contained.
// It requres usage of the example driver specific to your platform.
// See the HAL documentation.

#include "bindings/hal_common.h"
#include "bindings/bricklet_distance_us_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Distance US Bricklet 2.0

void check(int rc, const char* msg);

void example_setup(TF_HalContext *hal);
void example_loop(TF_HalContext *hal);


// Callback function for distance callback
static void distance_handler(TF_DistanceUSV2 *device, uint16_t distance,
                             void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Distance: %d 1/%d cm\n", distance, 10);
}

static TF_DistanceUSV2 dus;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_distance_us_v2_create(&dus, UID, hal), "create device object");

	// Register distance callback to function distance_handler
	tf_distance_us_v2_register_distance_callback(&dus,
	                                             distance_handler,
	                                             NULL);

	// Configure threshold for distance "greater than 100 cm"
	// with a debounce period of 0.1s (100ms)
	tf_distance_us_v2_set_distance_callback_configuration(&dus, 100, false, '>', 100*10, 0);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
