# Device Discovery

This file describes the MIDI device discovery process. It's a part of MIDI standard, yet worth describing in condensed form, with E-mu specific data included.

## Request

In order to detect MIDI device(s), software sends a *Device Inquiry* SysEx message of the form:

```
F0 7E <deviceId> 06 01 F7 
```

Where:

 * `0xF0` marks the start of SysEx MIDI message
 * `0x7E` denotes so-called *Universal Non-Real Time System Exclusive* message
 * `<deviceId>` is a target device ID, typically `0x7F`, meaning *all devices*
 * `0x06` denotes a message sub-ID#1: *General Information*
 * `0x01` denotes a message sub-ID#2: *Identity Request*
 * `0xF7` marks the end of SysEx MIDI message (aka `EOX`, for *End Of eXclusive*)


## Response

The device which receives the request responds with the following message:

```
F0 7E <deviceId> 06 02 <mm> [<mm> <mm>] <ff> <ff> <dd> <dd> <ss> <ss> <ss> <ss> F7 
```

Where:

 * `0xF0` marks the start of SysEx MIDI message
 * `0x7E` denotes so-called *Universal Non-Real Time System Exclusive* message
 * `<deviceId>` is a device ID of the responding device
 * `0x06` denotes a message sub-ID#1: *General Information*
 * `0x02` denotes a message sub-ID#2: *Identity Reply*
 * `<mm>` is a manufacturer ID, if first byte is `0x00`, 2 extra bytes are sent
 * `<ff> <ff>` denote device family code (vendor specific), LSB first
 * `<dd> <dd>` denote device member code (vendor specific), LSB first
 * `<ss> <ss> <ss> <ss>` denote software revision level
 * `0xF7` marks the end of SysEx MIDI message (aka `EOX`, for *End Of eXclusive*)
 
Note:

 * as with every SysEx devices, all bytes between start and `EOX` have most-significant bit cleared
 * manufacturer ID for *E-mu Systems* is `0x18`

