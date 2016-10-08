# GPIB (IEEE-488) to usb adapter

![gpib2usb](doc/cad.png)

We live in wonderful times... Now is possible for us to get wonderful, old and used measurement equipment on e-bay, just for a few bucks. Equipment that otherwise would be out of  the hobbist leage, like 6.5 digit multimeters, oscilloscopes, signal generators... just to name a few.

These old equipment often come with a GPIB interface, which allows to control them from a computer with the corresponding GPIB connection. Regretably, computers do not come with GPIB interfaces, and the adapters available are not cheap.

Here comes this little device to rescue. It is a gpib-to-usb adapter which after connected to the computer via the almighty usb port, it presents itself as a serial port and allows to send GPIB commands to connected GPIB devices.

For now is yet a work in progress.

# USB Interface

The device presents itself as a serial port. Following commands are supported:

| Command	 | Description |
|----------|-------------|
|++addr 0-31|	Tell controller which device to address [Default set by DIP switch]|
|++addr	| Query currently configured device address
|++clr	| Issue device clear
|++eoi 0/1|	Enable (1) or disable (0) EOI with last byte. Default is 0.
|++eoi	|Query current EOI setting
|++eos 0/1/2/3	|EOS terminator — 0:CR+LF, 1:CR, 2:LF, 3:None. Default is 0.
|++eos	|Query current EOS setting
|++ifc	|Issue interface clear
|++loc	|Return device to local mode
|++spoll	|Read status byte by serial polling the device
|++srq	|Query status of SRQ line. 0: Not asserted, 1:Asserted
|++trg	|Issue device trigger
|++ver	|Query GPIB-USB controller version
|++help	|Print help about commands

To send binary data to instruments following characters must be escaped by preceding them with an ESC character:
CR (ASCII 13), LF (ASCII 10), ESC (ASCII 27), ‘+’ (ASCII 43)

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
