# Contributing to daleiDB
:thumbsup: Thank you for contributing to daleiDB!

This project is still in development from scratch. Before you get started,
please read the [roadmap](ROADMAP.md) and [docs](doc/html/index.html) to
understand the current status and future todos of daleiDB.

### Styleguides
#### C++
- This project uses **C++ standard version 17**. Please make sure that your
compiler and code are compatible with the C++17 standard.
- Please use `.cpp` for C++ source file extension and `.hpp` for C++ header file
extension.
- Please write self-describing code. Use normal comments to explain code
segments internally. Use Doxygen-style comments for public documentation (please
read [Doxygen manual](http://www.doxygen.nl/manual/index.html) for your
reference).
- For coding style, naming conventions, etc., please strictly adhere to
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

#### Git commit messages
- Please use the present tense ("Fix a bug" not "Fixed a bug").
- Please use the imperative mood ("Implement a feature" not "Implements a
feature").
- Please limit the first line to 72 characters or less. Put explanations or
references of issues and pull requests after the first line.
- When changes are not relevant in building the project, include `[skip ci]` in
the commit title.
