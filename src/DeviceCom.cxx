// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
#include <usb.h>
#include <iostream>
#include "DeviceCom.h"

bool DeviceCom::init(void) {
    std::cout << "DeviceCom::init INI";
	struct usb_bus *bus;
	int error;
	handle = NULL;
	usb_init();
	usb_set_debug(0);
	usb_find_busses();
	usb_find_devices();
	for (bus = usb_get_busses(); bus; bus = bus->next) {
    	struct usb_device *dev;
		for (dev = bus->devices; dev; dev = dev->next) {
      		if (dev->descriptor.idVendor == 0x11ac && dev->descriptor.idProduct == 0x5455) {
        		handle = usb_open(dev);
				interface = dev->config->interface->altsetting->bInterfaceNumber;
				error = usb_claim_interface(handle, interface);
				if (error < 0) {
	  				usb_detach_kernel_driver_np(handle, interface);
	  				error = usb_claim_interface(handle, interface);
	  				if (error < 0) {
	    				usb_release_interface(handle, interface);
  	    				usb_close(handle);
	    				return false;
	  				}
				}
				break;
      		}
    	}
	}
	if (handle == NULL) return false;
    std::cout << "DeviceCom::init END";
    return true;
}

bool DeviceCom::read(int requestType,int request, int value, unsigned char *buffer, int size) {
    std::cout << "DeviceCom::read INI";
	if ( usb_control_msg(handle, requestType, request, value, 0x0, (char *)buffer, size, 1000)< 0 ) return false;
    std::cout << "DeviceCom::read END";
	return true;
}

int DeviceCom::readInt(int requestType,int request, int value, unsigned char *buffer, int size) {
    std::cout << "DeviceCom::readInt INI";
	return usb_control_msg(handle, requestType, request, value, 0x0, (char *)buffer, size, 1000);
}

bool DeviceCom::write(int requestType,int request, int value, unsigned char *buffer, int size) {
    std::cout << "DeviceCom::write INI";
	if ( usb_control_msg(handle, requestType, request, value, 0x0, (char *)buffer, size, 1000)< 0 ) return false;
	return true;
}

void DeviceCom::close(void) {
    std::cout << "DeviceCom::close INI";
	usb_release_interface(handle, interface);
	usb_close(handle);
    std::cout << "DeviceCom::close END";
}
