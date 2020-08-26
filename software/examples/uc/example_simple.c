#include "bindings/hal_common.h"
#include "bindings/bricklet_distance_us_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Distance US Bricklet 2.0

void check(int rc, const char* msg);

TF_DistanceUSV2 dus;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_distance_us_v2_create(&dus, UID, hal), "create device object");

	// Get current distance
	uint16_t distance;
	check(tf_distance_us_v2_get_distance(&dus, &distance), "get distance");

	tf_hal_printf("Distance: %d 1/%d cm\n", distance, 10.0);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
