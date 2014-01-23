# E-Mu firmware file

This document describes the format of the files used to update the E-Mu firmware (using eLoader). All the information below comes from eLoader code analysis.

The firmware files are binary files, with constant length header immedaitely followed by the firmware image. Header contains a CRC32 checksum of the firmware image part. The files are expected to have `.dli` (Downloadable Image?) extension.

## Strings

The file's header contains a few string fields, which are stored as follows:

 * each string field has a maximum length defined (i.e. field length)
 * if actual string is shorter than the field length, it's padded with `0x00` bytes (i.e. reminder of the field is filled with zeros)
 * character coding is most likely irrelevant, assuming `iso-8859-1` 

## Header

The file starts with a header containing the following fields:


| Offset | Name              | Type          | Description                                        |
|--------|-------------------|---------------|----------------------------------------------------|
| 0      | `magic`           | `string(32)`  | magic string used to confirm the file format       |
| 32     | `headerVersion`   | `uint32`      | must be equal to 1                                 |
| 36     | `startOffset`     | `uint32`      | offset in the file where the firmware image starts |
| 40     | `imageLength`     | `uint32`      | size of the firmware image                         |
| 44     | `checksum`        | `uint32`      | CRC32 checksum of the firmware image (see below)   |
| 48     | `compressionType` | `string(16)`  | expected to be `"none"`                            |
| 64     | `imageName`       | `string(32)`  | has to match the name requested by the device (see the upgrade process description) |
| 96     | `imageType`       | `string(16)`  | has to match the type requested by the device (see the upgrade process description) |
| 112    | `imageVersion`    | `string(16)`  | textual version number, not used |
| 128    | `imageTarget`     | `string(32)`  | determines the target device for which the firmware is applicable, see below |
| 160    | `properties`      | `string(256)` | not used (some *key=value* pairs in text format)   |

Note:

 * `string(n)` means a string of at most *n* characters, occupying exactly *n* bytes in the file
 * `magic` field is expected to contain `"Copyright E-mu Systems"` string (22 characters)
 * integers are stored **big endian** (natural format for Java)
 * `startOffset + imageLength` is expected to give the total size of the file

## Checksum

The CRC32 checksum is calculated over the image file, header itself is not included in the calculation. The CRC32 variant used by the eLoader application is the one implemented by `java.util.zip.CRC32` class. 

Equivalent CRC-32 generator can be generated using [pycrc]([http://www.tty1.net/pycrc/) utility with `--model crc-32` parameter.
