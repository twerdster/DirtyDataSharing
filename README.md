# DirtyDataSharing

[![C++](https://img.shields.io/badge/code-C%2B%2B-00599C?logo=c%2B%2B&logoColor=white)](Server.h)
[![Boost.Interprocess](https://img.shields.io/badge/dependency-Boost.Interprocess-555555)](Client.h)
[![Status: unsafe experiment](https://img.shields.io/badge/status-unsafe%20experiment-b45309)](#original-code)

A quick and dirty, very unsafe way of sharing data between processes. No locks. No safe guards. No error checking. Nothing.

![Conceptual diagram: a producer writes bytes to named shared memory, and a consumer or MATLAB MEX reader copies bytes out, with no active locking or bounds checks](docs/images/shared-memory-schematic.svg)

*Conceptual illustration of the original code, not a runtime demonstration. Declaring a mutex in
the shared structure does not synchronize the byte copies: the locking call is commented out.*

## Original code

- [Server.h](Server.h) creates and maps a named shared-memory object and writes into its 1 MiB data array.
- [Client.h](Client.h) maps the same object and copies a requested byte range.
- [getShared.cpp](getShared.cpp) exposes the reader through a MATLAB MEX entry point.

The original implementation is unchanged. It provides no active locking or bounds validation,
and is not a safe interchange layer for production or untrusted inputs. This README update did
not compile or execute it. No new software license is assigned by the documentation changes.
