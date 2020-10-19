# LP natives

Builds natives for lavaplayer and jda-nas for more architectures than the default:

- Darwin (Mac OS), x86-64
- Freebsd, x86-64
- Linux (glibc), aarch64
- Linux (glibc), arm
- Linux (glibc), x86
- Linux (glibc), x86-64
- Linux (musl), aarch64
- Linux (musl), x86-64
- Windows, x86
- Windows, x86-64

MP3 natives are *not* included, so using them will throw UnsatisfiedLinkError.

`src/connector` and `src/udpqueue` are the same code in [lavaplayer](https://github.com/sedmelluq/lavaplayer/tree/bec39953a037b318663fad76873fbab9ce13c033/natives/connector)
and [jda-nas](https://github.com/sedmelluq/jda-nas/tree/c3adb668c8bbdf3a7dca381f3047fa3a508194df/udp-queue-natives/udpqueue)