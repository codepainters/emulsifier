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
 * *eLoader* waits for the response for 200ms
 
## Constants

Family/member codes defined by eLoader for E-mu:

| Family code | Member code | Model              |
|---------------------------|--------------------|
| `0B 00`     | `0B 00`     | Darwin             |
| `04 04`     | `00 02`     | Audity 2000        |
| `04 04`     | `00 03`     | Proteus 2000       |
| `04 04`     | `00 04`     | B-3                |
| `04 04`     | `00 05`     | XL-1               |
| `04 04`     | `00 06`     | Virtuoso 2000      |
| `04 04`     | `00 07`     | Mo-Phatt           |
| `04 04`     | `00 08`     | B-3 Turbo          |
| `04 04`     | `00 09`     | XL-1 Turbo         |
| `04 04`     | `00 0A`     | Mo-Phatt Turbo     |
| `04 04`     | `00 0B`     | Planet Earth       |
| `04 04`     | `00 0C`     | Planet Earth Turbo |
| `04 04`     | `00 0D`     | XL-7               |
| `04 04`     | `00 0E`     | MP-7               |
| `04 04`     | `00 0F`     | Proteus 2500       |
| `04 04`     | `00 10`     | Orbit-3            |
| `04 04`     | `00 11`     | PK-6               |
| `04 04`     | `00 12`     | XK-6               |
| `04 04`     | `00 13`     | MK-6               |
| `04 04`     | `00 14`     | Halo               |
| `04 04`     | `00 15`     | Proteus 1000       |
| `04 04`     | `xx 08`     | Proteus MPS        |
| `04 01`     | `05 00`     | E4                 |
| `04 01`     | `05 01`     | e64                |
| `04 01`     | `05 02`     | E4K                |
| `04 01`     | `05 03`     | E64 FX             |
| `04 01`     | `05 04`     | E4XT               |
| `04 01`     | `05 05`     | E4X                |
| `04 01`     | `05 06`     | e6400              |
| `04 01`     | `05 07`     | E4 Ultra Turbo     |
| `04 01`     | `05 06`     | E4 Ultra           |

Note: 

 * Proteus MPS uses some fallback check - if nothing else matches, check is performed with member code MSB ignored (hence `xx` in the table). I don't know why.
 * devices with `04 04` family code and `00` member code MSB belong to *Proteus* faimly
 * devices with `04 01` family code and `05` member code MSB belong to *EOS* faimly
 