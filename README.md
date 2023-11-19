# AIOC-PTT
AIOC (All-In-One-Cable) PTT control via DTR/RTS Serial interface.

This is simple tool to allow you control the PTT of hendheld radio via [AIOC (All-In-One-Cable)](https://github.com/skuep/AIOC).
This tool uses the DTR/RTS on the serial interface.

Since the PTT cannot be held after the program finish execution, you will have to pass a `<command>` as argument, to be executed while the PTT is ON.

# Usage
`./aioc-ptt <device> <command>`
### hold the PTT for 5 seconds
`./aioc-ptt /dev/ttyACM1 'sleep 5'`
### execute command while holding the PTT.
`./aioc-ptt /dev/ttyACM1 'aplay -D hw:AllInOneCable /usr/share/sounds/alsa/Front_Center.wav'`


# Similar tools
If you're looking for a way to enable end disable PTT in separate commands, you will have to use the CM108 interface.

Here is a one [tool](https://github.com/twilly/cm108) to help you with that. And here is a simple bash script to help you with the tool:

```bash
#!/bin/bash
hidraw_dev=`./cm108 -p | grep "All-In-One-Cable" | grep -oP "/dev/hidraw\d+"`

case "$1" in
  1) ./cm108 -H $hidraw_dev -P 3 -L 1 ;;
  0) ./cm108 -H $hidraw_dev -P 2 -L 1 ;;
  *) echo "Usage: $0 [1|0]"; exit 1 ;;
esac
```

