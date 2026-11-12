# DirtyDataSharing context

## Purpose

Historical C++/MATLAB experiment that copies byte ranges through a named shared-memory object containing a 1 MiB array.

## Implementation evidence

All three source files were inspected. A static guard limits setup to its first call and is not reset by shutdown. The copies do not acquire the declared mutex, and offsets/sizes and MEX arguments are not validated.

Key entry points: `Server.h`, `Client.h`, `getShared.cpp`.

## Documentation state

The README explains operations, requirements, validation scope and limitations. Its pre-existing explanatory SVG is retained and labeled as a schematic rather than a runtime result. Source files and attribution are unchanged.

## Validation scope

Documentation checks only; no C++ or MEX build, runtime execution, automated test suite or saved successful run.

## Limitations

Native shared-structure layout, unsynchronized copies, unchecked ranges, incomplete error reporting and destructive first setup of the object name.
