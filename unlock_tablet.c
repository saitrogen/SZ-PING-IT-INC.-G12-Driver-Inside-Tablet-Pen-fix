#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

// Your tablet's Vendor and Product ID
#define VENDOR_ID 0x08f2
#define PRODUCT_ID 0x6811

// The sequence of secret commands we discovered
unsigned char init_sequence[][8] = {
    {0x08, 0x03, 0xfc, 0x03, 0x87, 0x00, 0xff, 0xf0},
    {0x08, 0x07, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff},
    {0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x08, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x08, 0x01, 0xfc, 0x03, 0x87, 0x00, 0xff, 0xf0}
};

void send_command(libusb_device_handle *handle, unsigned char *data) {
    int r = libusb_control_transfer(
        handle,
        0x21, // bmRequestType: Host-to-device, Class, Interface
        0x09, // bRequest: SET_REPORT
        0x0308, // wValue: Feature Report 8
        2,      // wIndex: Interface 2
        data,
        8,      // wLength: 8 bytes
        1000    // timeout (ms)
    );

    if (r < 0) {
        fprintf(stderr, "Control transfer failed: %s\n", libusb_error_name(r));
    } else {
        printf("Successfully sent command: ");
        for(int i=0; i<8; i++) printf("%02x ", data[i]);
        printf("\n");
    }
}

int main(void) {
    libusb_device_handle *handle = NULL;
    int r;

    r = libusb_init(NULL);
    if (r < 0) {
        fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(r));
        return 1;
    }

    handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    if (handle == NULL) {
        fprintf(stderr, "Could not find or open the tablet.\n");
        libusb_exit(NULL);
        return 1;
    }

    printf("Tablet found. Detaching kernel driver if necessary...\n");
    libusb_detach_kernel_driver(handle, 2);

    r = libusb_claim_interface(handle, 2);
    if (r < 0) {
        fprintf(stderr, "Could not claim interface: %s\n", libusb_error_name(r));
        libusb_close(handle);
        libusb_exit(NULL);
        return 1;
    }

    printf("Interface claimed. Sending initialization sequence...\n");

    int num_commands = sizeof(init_sequence) / sizeof(init_sequence[0]);
    for (int i = 0; i < num_commands; i++) {
        send_command(handle, init_sequence[i]);
    }

    printf("Sequence sent. Releasing interface.\n");

    libusb_release_interface(handle, 2);
    libusb_attach_kernel_driver(handle, 2);
    libusb_close(handle);
    libusb_exit(NULL);

    printf("Tablet unlocked.\n");
    return 0;
}
