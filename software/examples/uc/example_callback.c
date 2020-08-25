#include "bindings/hal_common.h"
#include "bindings/bricklet_distance_us_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Distance US Bricklet 2.0

void check(int rc, const char* msg);

// Callback function for distance callback
void distance_handler(TF_DistanceUSV2 *device, uint16_t distance, void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Distance: %d 1/%d cm\n", distance, 10.0);
}

TF_DistanceUSV2 dus;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_distance_us_v2_create(&dus, UID, hal), "create device object");


	// Register distance callback to function distance_handler
	tf_distance_us_v2_register_distance_callback(&dus,
	                                            distance_handler,
	                                            NULL);

	// Set period for distance callback to 0.1s (100ms) without a threshold
	tf_distance_us_v2_set_distance_callback_configuration(&dus, 100, false, 'x', 0, 0);

}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
