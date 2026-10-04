/*
 * NVIDIA Interview Question:
 * Section 2.1: A Communications Protocol
 *
 * Question:
 * This problem concerns a packet-based communications protocol linking two
 * computing devices.
 *
 * Packet Structure:
 *   [SOP] [ ...data... ] [CSUM] [EOP]
 *   - SOP (Start of Packet): A single byte indicating the beginning of a packet.
 *   - Data Bytes: A variable number of data bytes (can be zero).
 *   - CSUM: A single byte indicating the sum (mod 256) of the data bytes,
 *           i.e., this does not include SOP or EOP.
 *   - EOP (End of Packet): A single byte indicating the end of a packet.
 *
 * a) Fill in the body of the function and list any assumptions that you have made.
 *    Function Prototype:
 *        int process_incoming_byte(uint8_t byte);
 *    Returns 1 if a complete and valid packet is detected.
 *    Returns 0 if the packet is incomplete or invalid.
 *
 * b) Can you suggest an alternative way of defining the checksum which would
 *    simplify the verification/processing?
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define SOP_BYTE 0x02  // ASCII STX (Start of Text)
#define EOP_BYTE 0x03  // ASCII ETX (End of Text)
#define MAX_PAYLOAD_SIZE 256

/*
 * ==============================================================================
 * ASSUMPTIONS MADE FOR PART (a)
 * ==============================================================================
 * 1. Protocol Delimiters:
 *    - SOP is defined as a dedicated unique delimiter byte (e.g., 0x02).
 *    - EOP is defined as a dedicated unique delimiter byte (e.g., 0x03).
 *    - If arbitrary binary payload is allowed, standard byte stuffing (escaping)
 *      is assumed, OR SOP/EOP bytes do not collide with unescaped data.
 * 2. Packet Sizing:
 *    - The payload (data bytes) can range from 0 up to MAX_PAYLOAD_SIZE (256 bytes).
 *    - A buffer is used to collect bytes between SOP and EOP.
 * 3. CSUM Position:
 *    - Because payload length is variable, CSUM is the byte immediately preceding EOP.
 *    - If 0 data bytes: [SOP][CSUM=0x00][EOP] (total packet = 3 bytes).
 * 4. Error Recovery & Synchronization:
 *    - If SOP arrives unexpectedly in the middle of a packet, the state machine resets
 *      and begins receiving the new packet immediately.
 *    - If the buffer overflows before EOP arrives, the packet is discarded and the
 *      state resets to WAIT_FOR_SOP.
 */

typedef enum {
    STATE_WAIT_FOR_SOP,
    STATE_COLLECT_PACKET
} RxState;

static RxState rx_state = STATE_WAIT_FOR_SOP;
static uint8_t rx_buffer[MAX_PAYLOAD_SIZE + 2]; // holds data + CSUM
static size_t rx_count = 0;

// Expose received payload to caller
static uint8_t last_valid_payload[MAX_PAYLOAD_SIZE];
static size_t last_valid_len = 0;

int process_incoming_byte(uint8_t byte)
{
    // Resynchronization: SOP resets the receiver to start of packet
    if (byte == SOP_BYTE) {
        rx_state = STATE_COLLECT_PACKET;
        rx_count = 0;
        return 0; // Packet in progress
    }

    if (rx_state == STATE_WAIT_FOR_SOP) {
        // Discard any bytes received prior to SOP
        return 0;
    }

    // When collecting packet:
    if (byte == EOP_BYTE) {
        // Minimum valid packet after SOP: [CSUM][EOP] => rx_count must be at least 1 (the CSUM)
        if (rx_count < 1) {
            rx_state = STATE_WAIT_FOR_SOP;
            return 0; // Malformed: No CSUM byte before EOP
        }

        // Last byte before EOP is CSUM
        uint8_t received_csum = rx_buffer[rx_count - 1];
        size_t data_len = rx_count - 1;

        // Calculate sum (mod 256) of data bytes
        uint8_t calculated_csum = 0;
        for (size_t i = 0; i < data_len; i++) {
            calculated_csum = (uint8_t)(calculated_csum + rx_buffer[i]);
        }

        rx_state = STATE_WAIT_FOR_SOP;

        if (calculated_csum == received_csum) {
            // Valid packet received!
            memcpy(last_valid_payload, rx_buffer, data_len);
            last_valid_len = data_len;
            return 1;
        } else {
            // Checksum mismatch
            return 0;
        }
    }

    // Collect data byte / CSUM byte into buffer
    if (rx_count < sizeof(rx_buffer)) {
        rx_buffer[rx_count++] = byte;
    } else {
        // Buffer overflow: discard corrupted packet
        rx_state = STATE_WAIT_FOR_SOP;
        rx_count = 0;
    }

    return 0;
}

/*
 * ==============================================================================
 * PART (b): ALTERNATIVE CHECKSUM DEFINITIONS TO SIMPLIFY PROCESSING
 * ==============================================================================
 *
 * 1. Two's Complement Checksum (Negative Sum / Zero-Sum Check):
 *    - Definition: CSUM is defined such that:
 *          CSUM = (-sum(data_bytes)) & 0xFF;
 *    - Simplification:
 *      During verification on the receiver, you simply add all data bytes AND the
 *      CSUM byte to a single running 8-bit accumulator:
 *          running_sum = (running_sum + byte) & 0xFF;
 *      When EOP arrives, valid packet check simplifies to a single comparison:
 *          if (running_sum == 0) -> Valid!
 *      No need to store CSUM separately or subtract it before comparison.
 *
 * 2. XOR Checksum (Longitudinal Redundancy Check - LRC):
 *    - Definition: CSUM is the bitwise XOR of all data bytes:
 *          CSUM = byte_0 ^ byte_1 ^ ... ^ byte_N-1;
 *    - Simplification:
 *      Extremely fast in embedded microcontrollers (single cycle, no carry
 *      propagation). When verifying, XORing all bytes including CSUM results in 0.
 *
 * 3. Including Length in Header:
 *    - e.g., [SOP][LEN][ ...data... ][CSUM][EOP]
 *    - Allows pre-allocating buffer and knowing exactly which byte is CSUM without
 *      waiting for EOP to demarcate the CSUM.
 */

int main(void)
{
    printf("=== Testing Communications Protocol State Machine ===\n\n");

    // Test Case 1: Packet with 3 data bytes [0x10, 0x20, 0x30], CSUM = 0x60
    uint8_t stream1[] = {0xFF, SOP_BYTE, 0x10, 0x20, 0x30, 0x60, EOP_BYTE};
    printf("Sending Valid Packet: [SOP][0x10, 0x20, 0x30][CSUM=0x60][EOP]\n");
    for (size_t i = 0; i < sizeof(stream1); i++) {
        if (process_incoming_byte(stream1[i])) {
            printf(" -> Packet successfully detected and validated! (Payload len: %zu)\n", last_valid_len);
        }
    }

    // Test Case 2: Zero-length data packet: [SOP][CSUM=0x00][EOP]
    uint8_t stream2[] = {SOP_BYTE, 0x00, EOP_BYTE};
    printf("\nSending Zero-Length Data Packet: [SOP][CSUM=0x00][EOP]\n");
    for (size_t i = 0; i < sizeof(stream2); i++) {
        if (process_incoming_byte(stream2[i])) {
            printf(" -> Zero-length packet successfully validated! (Payload len: %zu)\n", last_valid_len);
        }
    }

    // Test Case 3: Corrupt packet: CSUM mismatch
    uint8_t stream3[] = {SOP_BYTE, 0x10, 0x20, 0x99, EOP_BYTE};
    printf("\nSending Corrupt Packet (Invalid CSUM): [SOP][0x10, 0x20][CSUM=0x99][EOP]\n");
    bool detected = false;
    for (size_t i = 0; i < sizeof(stream3); i++) {
        if (process_incoming_byte(stream3[i])) {
            detected = true;
        }
    }
    printf(" -> Result: %s\n", detected ? "Accepted (Bug!)" : "Rejected correctly!");

    return 0;
}
