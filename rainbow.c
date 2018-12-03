#include "device.h"
#include "driver.h"
#include "logic/options.h"
#include "logic/scan.h"
#include "print.h"

#include <errno.h>
#include <libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "rainbow.h"

struct RGB
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

struct HSV
{
    double H;
    double S;
    double V;
};

struct RGB HSVToRGB(struct HSV hsv) {
    double r = 0, g = 0, b = 0;

    if (hsv.S == 0)
    {
        r = hsv.V;
        g = hsv.V;
        b = hsv.V;
    }
    else
    {
        int i;
        double f, p, q, t;

        if (hsv.H == 360)
            hsv.H = 0;
        else
            hsv.H = hsv.H / 60;

        i = (int)trunc(hsv.H);
        f = hsv.H - i;

        p = hsv.V * (1.0 - hsv.S);
        q = hsv.V * (1.0 - (hsv.S * f));
        t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

        switch (i)
        {
        case 0:
            r = hsv.V;
            g = t;
            b = p;
            break;

        case 1:
            r = q;
            g = hsv.V;
            b = p;
            break;

        case 2:
            r = p;
            g = hsv.V;
            b = t;
            break;

        case 3:
            r = p;
            g = q;
            b = hsv.V;
            break;

        case 4:
            r = t;
            g = p;
            b = hsv.V;
            break;

        default:
            r = hsv.V;
            g = p;
            b = q;
            break;
        }

    }

    struct RGB rgb;
    rgb.R = r * 255;
    rgb.G = g * 255;
    rgb.B = b * 255;

    return rgb;
}

void start_rainbow(
    struct corsair_device_scan scanned_device,
    struct option_flags flags,
    struct option_parse_return settings) {

    struct corsair_device_info *dev = scanned_device.device;
    struct libusb_device_handle *handle = scanned_device.handle;

    int rr = dev->driver->init(handle, dev->write_endpoint);

    uint8_t response[64];
    uint8_t commands[64];
    memset( response, 0, sizeof( response ) );
    memset( commands, 0, sizeof( commands ) );

    int r = 1;
    int g = 2;
    int b = 3;

    commands[0] = 0x10;
    commands[1] = 0x00; //ctrl->led_colors[0].red;
    commands[2] = 0xff; //ctrl->led_colors[0].green;
    commands[3] = 0x00; //ctrl->led_colors[0].blue;
    commands[4] = 0x00;
    commands[5] = 0xff;
    commands[6] = 0xff;
    commands[7] = 0xff;
    commands[8] = 0x00;
    commands[9] = 0x00;
    commands[10] = 0x37; // 0x37 = 55C, 0x2d = 45C
    commands[11] = 0x0a; // FadeThobInterval
    commands[12] = 0x05; // ThrobSequence
    commands[13] = 0x01; // LED Enable
    commands[14] = 0x00; // Fade Enable
    commands[15] = 0x00; // Throb Enable
    commands[16] = 0x00; // Warning_Enable
    commands[17] = 0x00; // BootMode
    commands[18] = 0x01; // FanType


    while(1) {
        for (int i = 0; i < 360; i++) {
            struct HSV hsv = { i, 1.0, 0.60 };

            struct RGB rgb = HSVToRGB(hsv);
            commands[r] = rgb.R;
            commands[g] = rgb.G;
            commands[b] = rgb.B;

            rr = dev->driver->write( handle, dev->write_endpoint, commands, 19 );
            rr = dev->driver->read( handle, dev->read_endpoint, response, 32 );

            usleep(1 * 1000);
        }
    }
}