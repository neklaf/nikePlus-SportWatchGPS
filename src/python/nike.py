#! /usr/bin/python2
# -*- coding: iso-8859-15 -*-
NIKE_VENDOR_ID = 0x11ac
NIKE_PRODUCT_ID = 0x5455

import usb.core
import usb.util
import usb.control

dev = usb.core.find(idVendor=NIKE_VENDOR_ID, idProduct=NIKE_PRODUCT_ID)

if dev.is_kernel_driver_active(0):
    print('Detaching kernel driver\n')
    dev.detach_kernel_driver(0)

cfg = usb.util.find_descriptor(dev, bConfigurationValue=1)
iface = cfg[(0,0)]

bytes_num = [ 0x09 , 0x02 , 0x29 , 0x08 , 0x00 , 0x00 , 0x00 , 0x00 ,
        0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
        0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
        0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
        0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
        0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
        0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
        0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ]
data_raw="".join(map(chr,bytes_num))
iface[1].write(data_raw)
version=iface[0].read(64)
letter=chr(version[3])
code=version[5]<<8+version[4]
print("Version:�%s%d"%(letter,code))
