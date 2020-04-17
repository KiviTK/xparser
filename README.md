# xparser
A simple C++ utility to parse files for Xresources color replacement (stream editor style)

## Dependencies
You need to have `xgetres` installed for this thing to work, as it is used to get the values.

## How to use
Just build the cpp file with g++ or whatever you use, no psecial treatment needed, I think C++11 and above should work.
Then pipe a file into it, and it will output it parsed.
The default parsing prefix is `$XC` which means that this: `$XC 3` will be replaced with your third xresources color,
something like `#DE935F`.
You can change this prefix with the `-p` flag, like so: `xparser -p MY_PREF`.

Some special colors are supported too, like `fg`(.foreground) `bg`(.background) and `cur`(.cursorColor), so like `$XC cur` will be replaced with your `*.cursorColor`

## Warning!
This will replace ALL white spces with a single space (except line breaks, line breaks will be line breaks)
You also need to have the exact sequence, so for example this wont work: `$XC 1;` you need to leave whitespaces!
Ther working version is this: `$XC 1 ;`.
