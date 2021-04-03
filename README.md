<p align=center>
  <span><strong>Lightweight username lookup inspired by <a href="https://github.com/sherlock-project/sherlock">Sherlock</a>. Created in C++.</strong></span>
  <br>
  <a target="_blank" href="https://isocpp.org" title="c++20"><img src="https://img.shields.io/badge/C++-20-blue.svg"></a>
  <a target="_blank" href="license" title="License: MIT"><img src="https://img.shields.io/badge/License-MIT-red.svg"></a>
  <a target="_blank" href="https://github.com/EternalRift/scout/releases" title="releases"><img src="https://img.shields.io/badge/Release-1.0-brightgreen.svg"></a>
</p>

### How to build
#### Prerequisites
* cpr (curl-for-people)
* nlohmann-json

#### Using vcpkg
<a target="_blank" href="https://github.com/microsoft/vcpkg#quick-start-windows" title="install-vcpkg">How to install vcpkg</a>
```console
vcpkg install cpr:x86-windows-static
vcpkg install nlohmann-json:x86-windows-static
```

#### Compiling
```console
# clone the repo
$ git clone https://github.com/EternalRift/scout.git
```

* Open scout.sln with Visual Studio 2019 and compile with x86 Release
