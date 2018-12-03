
GTXH100i_rainbow is a useless stripped down version of OpenCorsairLink https://github.com/audiohacked/OpenCorsairLink to generate rgb rainbow with the GTXH100i pump RGB led.



### Disclaimer
> __DISCLAIMER__: GTXH100i_rainbow is not an official Corsair product. It is licensed under the GNU General Public License (version 2) in the hope that it will be useful, but with NO WARRANTY of any kind. Corsair and Corsair Link are trademarks or registered trademarks of Corsair Components, Inc. The trademark holders are not affiliated with the maker of this product and do not endorse this product.

## Installation

## REFER TO https://github.com/audiohacked/OpenCorsairLink

```
$ make
```

## Usage
Since the program needs direct hardware access you should run this with 'sudo' or as root.  

```
$ sudo ./GTXH100i_rainbow
$ sudo ./GTXH100i_rainbow --help
```

## Start RGB Rainbow on GTXH100i

```
$ sudo ./GTXH100i_rainbow --device 0
```

You should first run https://github.com/audiohacked/OpenCorsairLink in order to find the correct device number


## FAQs

### Why isn't this feature present in the CorsairLink Windows software? 

I don't know.