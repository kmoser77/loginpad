# Login Pad

This is my second arduino project. This little project is inteded to simmulate a keyboard to automatically provide credentials for non-critical logins e.g. on development websites. Do not use this to store sensitive login data like bank accounts or shopping portals like amazon as there is no encryption (yet) in the box.

Visit the [project page](https://www.fam-moser.de/blog/kmosers-tech-blog/computer/iot/loginbox.html) (in german) for more details. 

## Hardware

Wiring is very simple.
![Arduino wiring](https://raw.githubusercontent.com/kmoser77/loginpad/master/images/ProMicro_wiring.jpg "Wiring")

## Compile

Before you can compile this sketch you have to copy the *ext_def-example.h* to *ext_def.h*, modify the pin setting and add some keypresses to the key arrays.

### Change pin

```c++
#define PIN "123456"
```

### Change button definitions

Set A uses `values0_0` to `values0_9`, Set B `values1_0` to `values1_9`, and so on...

```c++
const PROGMEM char values0_0[]  = {0x54,0x65,0x73,0x74,0xB0,0x00};
```

This outputs "Test↲" when pressing key 0 in Set A. There are some special characters like `0x00` which indicates the end of the string. You may also need `0xB0` which is the *Enter* Key or `0xB3` which is the *Tab* Key.
