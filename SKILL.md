# DirtyDataSharing maintenance workflow

Read `SUMMARY.md`, this file and `README.md` before editing.

## Working on the repository

Review the writer, reader and MEX entry point together. MATLAB builds require a MEX C++ compiler and Boost headers; do not describe the illustrative command as tested. Source redesign is separate work.

## Documentation checks

- Check claims against the named source files and recorded results. Separate source inspection,
  configuration generation, runtime execution and benchmark evidence.
- Keep README setup requirements available without following an advanced guide. Check Markdown
  headings, links and image references, including source files omitted by a sparse checkout.
- Inspect labels inside diagrams as well as captions. Never turn a schematic or generated input
  into an implied successful run.
- Keep original source, credits and license notices intact for documentation-only changes.
- Review and synchronize `SUMMARY.md` and `SKILL.md` before every commit. Record any unrun checks
  as limitations rather than implying that validation passed.

## Current evidence boundary

Documentation checks only; no C++ or MEX build, runtime execution, automated test suite or saved successful run.

Native shared-structure layout, unsynchronized copies, unchecked ranges, incomplete error reporting and destructive first setup of the object name.
