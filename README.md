# flir_camera_driver

## Note about QT5 problems after installing spinnaker
Tip when installing spinnaker: Only install the actual library and not libspinview etc, as it pulls in QT dependencies that might break things on your system.

To do so, modify the install script (install_spinnaker.sh) to not include any of the spinvideo/spinview packages (on line 38 and following)

## How to install
* Get the Spinnaker SDK from https://www.flir.com/products/spinnaker-sdk/.<br />
Direct link to most recent SpinnakerSDK for Linux: https://flir.app.boxcn.net/v/SpinnakerSDK/folder/69083919457.

* Follow the instructions in the provided REAMDE to install the Spinnaker SDK on your system.

* The Spinnaker SDK depends on libunwind8:
```sudo apt install libunwind8-dev```
* The spinnaker_camera_driver package (part of this repository) depends on [image_numbered_msgs](https://github.com/ethz-asl/image_numbered_msgs.git)

### Increasing USB memory buffer
From [Pointgrey](https://www.ptgrey.com/tan/10685#ConfiguringUSBFS)

By default, Linux limits image capture to 2 MB. To capture images over 2 MB, extend the USBFS limit on how many buffers can be locked into the driver.

You can check your current buffer limit with
```
cat /sys/module/usbcore/parameters/usbfs_memory_mb
```

For capturing larger images, a buffer of ~1000 MB is recommended. Set it permanently by replacing the corresponding line in `/etc/default/grub` with the following:
```
GRUB_CMDLINE_LINUX_DEFAULT="nomodeset quiet splash usbcore.usbfs_memory_mb=1000"

```
followed by
```
sudo update-grub
```
and reboot.

Note! On Ubuntu 18.04 "nomodeset" can prevent the computer from recognizing additional monitors. Hence use the following instead
```
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash usbcore.usbfs_memory_mb=1000"

```

## Other stuff

[![Build Status](https://travis-ci.org/ros-drivers/flir_camera_driver.png?branch=kinetic-devel)](https://travis-ci.org/ros-drivers/flir_camera_driver)

This repository contains packages for FlirImaging's line of cameras. This repositories intent is to make use of Flir's newly developed SDK: Spinnaker. The camera driver is an evolution of pointgrey_camera_driver. It has been updated to use the new methods provided by the SDK.

## Packages

### Spinnaker Camera Driver
The camera driver supports USB3 and GIGE cameras are planned. Note thats support for FireWire cameras is dropped in this SDK. The driver has been tested with a Blackfly S and Chameleon 3 camera. Differences between cameras requires that each camera model needs a customized interface class.  If your camera type is not included, consider contributing the interface by referring to the section bellow.

##### Contributing
Due to differences in parameter naming the configuration is separated from the main library. `camera.cpp` contains the base class `Camera` which can be extended to accommodate different cameras. The base class is based on BlackFly S and `cm3.cpp` extends it adding support for Chameleon3. To add a camera create a new derived class of `Camera` and add the model name to the check in `SpinnakerCamera::connect`.

When contributing make sure the travis job suceeds and please use [roscpp_code_format](https://github.com/davetcoleman/roscpp_code_format) to format your code.

## Licence
ROS-compatible Camera drivers originally provided by NREC, part of Carnegie Mellon University's robotics institute.
These drives are included along with modifications of the standard ros image messages that enable HDR and physics based vision.

This code was originally developed by the National Robotics Engineering Center (NREC), part of the Robotics Institute at Carnegie Mellon University. Its development was funded by DARPA under the LS3 program and submitted for public release on June 7th, 2012. Release was granted on August, 21st 2012 with Distribution Statement "A" (Approved for Public Release, Distribution Unlimited).

This software is released under a BSD license:

Copyright (c) 2012, Carnegie Mellon University. All rights reserved.  
Copyright (c) 2018, Clearpath Robotics, Inc., All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the Carnegie Mellon University nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
