# Platform Abstraction #
  * Provides primitives needed to implement other libraries.
  * Not a single layer for all platform abstraction (ie file systems, threads, video, etc) as this would require extensions as new libraries are added.
    * Fixed size types
    * Function attributes (ie declaration spec/restrict/inline/noinline)

# File System #
  * A light weight file system wrapper. Most client functionality should use more specialized libraries built on top of this (ie user settings, save game, etc) as some of these require special per-platform implementations that don't map to device/file systems very well.

# Error #
  * Asserts, logging, crash dump
  * No exception use at this time due to recommendations from some platform providers.

# Threads #
  * Possible use of boost threads
    * Concerns about memory allocation behavior