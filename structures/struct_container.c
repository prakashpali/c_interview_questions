/**
 * Q: Given a structure and the address of one of its fields, find the starting
 *    address of the container structure (i.e., implement the Linux container_of macro).
 *
 * Explanation:
 * We know the address of a specific member inside a struct.
 * To find the start address of the struct, we simply subtract the byte offset of
 * that member from the member's address.
 *
 * Formula: struct_address = (char *)member_address - offset_of_member
 */

#include <stdio.h>
#include "../utils.h"

/**
 * Implement offset of a member
 */
#define my_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/**
 * Simple standard C implementation of container_of.
 */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - my_offsetof(type, member)))


/**
 * Example Structure
 */
struct sensor_data {
    int id;
    float temperature;
    int hardware_status;
};


int main(void)
{
    /* 1. Create our actual struct instance */
    struct sensor_data my_sensor = { .id = 42, .temperature = 98.6f, .hardware_status = 1 };

    /* 2. Imagine we are inside a callback function and we only get a pointer to the 'hardware_status' field! */
    int *status_ptr = &my_sensor.hardware_status;

    /* 3. We want to retrieve the whole 'sensor_data' structure from just that pointer. */
    struct sensor_data *container = container_of(status_ptr, struct sensor_data, hardware_status);

    printf("Original struct address : %p\n", (void *)&my_sensor);
    printf("Pointer to status field : %p\n", (void *)status_ptr);
    printf("Calculated struct addr  : %p\n", (void *)container);

    if (container == &my_sensor) {
        printf("\nSuccess! We recovered the container.\n");
        printf("Container ID: %d\n", container->id);
        printf("Temp: %.1f\n", container->temperature);
        printf("Hardware Status: %d\n", container->hardware_status);
    } else {
        printf("\nFailure!\n");
    }

    return 0;
}
