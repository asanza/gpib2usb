# GPIB (IEEE-488) to usb adapter

![gpib2usb](doc/cad.png)

We live in wonderful times... Now is possible for us to get wonderful, old and used measurement equipment on e-bay, just for a few bucks. Equipment that otherwise would be out of  the hobbist leage, like 6.5 digit multimeters, oscilloscopes, signal generators... just to name a few.

These old equipment often come with a GPIB interface, which allows to control them from a computer with the corresponding GPIB connection. Regretably, computers do not come with GPIB interfaces, and the adapters available are not cheap.

Here comes this little device to rescue. It is a gpib-to-usb adapter which after connected to the computer via the almighty usb port, it presents itself as a serial port and allows to send GPIB commands to connected GPIB devices.

For now is yet a work in progress. So wait for updates.

# USB Interface

The device presents itself as a serial port. Following commands are available:


# Know issues

## Disable modem manager in linux.

In order to detect new devices, modem manager issues two AT commands to each new ACM device detected. This blocks the serial port and causes it to be unavailable the first seconds. This is somewhat annoying. Fortunately it is possible to disable this behaviour. You need to create a new file:

```
/etc/udev/rules.d/77-mm-usb-device-blacklist.rules 
```
and put following content in it:

```
with content:
# gpib2usb converter
ATTRS{idVendor}=="1209", ATTRS{idProduct}=="0001", ENV{ID_MM_DEVICE_IGNORE}="1" 
```