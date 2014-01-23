from struct import Struct
from crc32 import crc32


class FirmwareImage(object):
    """
    Class representing a firmware image loaded from .dli file.
    """

    _HEADER = Struct(">32sIIII16s32s16s16s32s256s")
    _MAGIC = "Copyright E-mu Systems"

    def __init__(self, image_file):
        self.image_name = None
        self.image_type = None
        self.image_version = None
        self.image_target = None
        self.image = None

        self._start_offset = None
        self._image_length = None
        self._checksum = None

        self._read_header(image_file)
        self._read_image(image_file)

    def _read_header(self, image_file):
        header = image_file.read(self._HEADER.size)
        if len(header) < self._HEADER.size:
            raise FirmwareImageInvalidHeader("File too short")

        magic, header_version, self._start_offset, self._image_length, self._checksum,\
            compression_type, image_name, image_type, image_version, image_target, _ = self._HEADER.unpack(header)

        if magic.find(self._MAGIC) != 0:
            raise FirmwareImageInvalidHeader("Wrong magic string: '%s'" % magic)
        if header_version != 1:
            raise FirmwareImageInvalidHeader("Unsupported header version")
        if compression_type.rstrip('\0') != 'none':
            raise FirmwareImageInvalidHeader("Unsupported compression type")

        self.image_name = image_name.rstrip('\0')
        self.image_type = image_type.rstrip('\0')
        self.image_version = image_version.rstrip('\0')
        self.image_target = image_target.rstrip('\0')

    def _read_image(self, image_file):
        image_file.seek(0, 2)
        file_size = image_file.tell()

        if self._start_offset + self._image_length != file_size:
            raise FirmwareImageInvalidSize()

        image_file.seek(self._start_offset)
        self.image = image_file.read(self._image_length)

        if crc32(self.image) != self._checksum:
            raise FirmwareImageInvalidChecksum()

    def __str__(self):
        return "FirmwareImage(name='%s', type='%s', version='%s', target='%s')" % \
               (self.image_name, self.image_type, self.image_version, self.image_target)


class FirmwareImageException(Exception):
    pass


class FirmwareImageInvalidHeader(FirmwareImageException):
    pass


class FirmwareImageInvalidSize(FirmwareImageException):
    pass


class FirmwareImageInvalidChecksum(FirmwareImageException):
    pass


if __name__ == '__main__':
    import sys
    with open(sys.argv[1], 'r') as f:
        firmware = FirmwareImage(f)

    print str(firmware)
