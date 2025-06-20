# MBIM Decoder

Decodes either raw MBIM messages or from MikroTik RouterOS logs (static). Based on [MBIM v1.0 + Errata](https://www.usb.org/document-library/mobile-broadband-interface-model-v10-errata-1-and-adopters-agreement). Planned support for MBIMExt v2 and v3 (not implemented yet). Designed for use alongside the spec.

## Build

Requires:
- C++17 compiler
- POSIX environment (Linux/macOS)

```bash
make                                       # build main binary (mbimros)
make test                                  # build and run unit tests
make test_one TEST_FILE=tests/<file.cpp>   # build + run single test
make clean                                 # remove all build outputs
```

## Usage

```bash
./mbimros [flags]
```

### Flags

```
-i <file>          Input file (RouterOS log format)
-o <file>          Output decoded text to file
-r <hex>           Raw inline MBIM hex string
--no-header        Skip MBIM framing header decoding
--force-noext      Force interpret as MBIM v1.0 only
--force-ext2       Force interpret as MBIMExt v2
--force-ext3       Force interpret as MBIMExt v3
```

### Examples

```bash
./mbimros -i ros_log.txt -o decoded.txt
./mbimros -r "030000008000..." --no-header --force-noext
```


# TO DO
- Implement Information buffer inheritance (MBIM_CID_PIN_LIST requires)
- Add field formatter functions, for example, for coded rssi, ip addresses, etc.
