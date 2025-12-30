<hr>

<div align="center">
    <img src="https://raw.githubusercontent.com/saucer/saucer.github.io/master/static/img/logo.png" height="312" />
</div>

<p align="center">
    C-Bindings for <a href="https://github.com/saucer/saucer">saucer</a>
</p>

---

> [!NOTE]
> The bindings found in this repository do not wrap the C++ API completely.\
> All of the core functionality is wrapped, but serialization heavy parts such as the smartview are not, as it would not make sense to do so.
> Instead, users are encouraged to build their own serialization on top of the bindings provided here, by using the respective event callbacks[^1].

## Artifacts

**It is encouraged to use the artifacts produced in this repository** (see workflows) instead of building your own.\
The workflows build in all configurations (Debug, MinSizeRel, RelWithDebInfo, Release) and produce the following artifacts:

- Linux
  - Qt
    > It is recommended to use the WebKitGtk based bindings, as Qt is known to be a diva at times
  - WebKitGtk
- MacOS
  - WebKit
- Windows
  - WebView2
  - WebView2-Hack[^2]
  - WebView2-Rfl[^3]
  - WebView2-Hack-Rfl

## Building

In case one absolutely needs to build the bindings themselves, please install the following dependencies:

- Windows
  - Latest Toolchain
    - You need **at least** MSVC 19.44 or clang-cl 19

- MacOS
  - Latest Toolchain
    - It is recommended to use at least XCode 26.1.1 or LLVM-Clang 20

- Linux
  - Recent Toolchain
    - You need **at least** GCC 14 or Clang 20
      - This also means that we are usually targetting a relatively recent glibc version.
        Should that be a problem, please consider using AppImage, Flatpak or Snapcraft.

  - WebKitGtk
    - gtk4
    - libadwaita
    - webkitgtk-6.0
    - json-glib-1.0

  - Qt
    - qt6-base
    - qt6-declarative
    - qt6-svg
    - qt6-tools
    - qt6-translations
    - qt6-webchannel
    - qt6-webengine

With these dependencies installed run:

```sh
git clone https://github.com/saucer/bindings
cd bindings
cmake -B build
cmake --build build
```

That's it. In case you encounter any issues, please checkout the workflows of this repository or get in touch!

## Existing Bindings

Please checkout the [main repository](https://github.com/saucer/saucer) for a list of available bindings.
Also, beware that all bindings are community maintained and their conformance may vary.

---

[^1]: For more information, checkout the official repository to see how the smartview is actually implemented under the hood.

[^2]: See the documentation: https://saucer.app/getting-started/cmake/#msvc-mutex

[^3]: Uses the reflect-cpp serializer instead of Glaze
