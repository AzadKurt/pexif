# Pexif

Pexif ("purge exif") is a fast and lightweight tool for removing exif data from jpg files.
No compression or resizing will take place, i.e. each and every pixel that existed in a given image `x.jpg` before using pexif will still be at it's relative position in the corresponding `pexif_x.jpg`.

## Installation

Either download the binaries presented in the releases or generate the executable yourself by running `make`.

It is recommended to include the pexif binary in a folder that is part of the PATH-variable. That way, pexif can be easily run from every working directory inside a terminal such as cmd, PowerShell or bash via `pexif [...]`.

## Usage

`pexif .` removes the exif data from every jpg file in the current working directory.

`pexif (FILEPATH)+` removes the exif data from every jpg file identified by the given file path. At least one file path is needed. Absolute paths, relative paths, regular slashes and backslashes are supported. For each file path, the usage of slashes has to be consistent, although the usage of different kinds of slashes may differ between different file paths.

## Demo

### `pexif .`

![alt-text](.github/pexif-dir.gif)

### `pexif (FILEPATH)+`

![alt-text](.github/pexif-paths.gif)

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Notes

*   [Valgrind](https://valgrind.org/) has been utilized to check for memory leaks. No leaks could be found.
*   In order to fully understand the code, I highly recommend to read about the exif specification. One of the sources that helped me can be found [here](http://gvsoft.no-ip.org/exif/exif-explanation.html) ([archived version](http://web.archive.org/web/20180223111221/http://gvsoft.no-ip.org/exif/exif-explanation.html)).


## License

[MIT](LICENSE)