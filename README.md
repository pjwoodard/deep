# Deep - 2D Deep Space Survival

![Deep](https://github.com/pjwoodard/deep/actions/workflows/ci.yml/badge.svg)

![image](https://github.com/user-attachments/assets/c364e2c8-bfce-4592-98cc-2f9859b7fee7)

# Build Instructions (Windows)
```bash
conan install . --output-folder=build -s build_type=Release -s compiler.cppstd="20" --build=missing
conan install . --output-folder=build -s build_type=Debug -s compiler.cppstd="20" --build=missing

cmake --preset conan-default

cmake --build ./build --preset conan-release
cmake --build ./build --preset conan-debug
```
# Build Instructions (Linux)
```bash
conan install . --output-folder=build -s build_type=Release -s compiler.cppstd="20" --build=missing
conan install . --output-folder=build -s build_type=Debug -s compiler.cppstd="20" --build=missing

cmake --preset conan-debug
cmake --preset conan-release

cmake --build ./build --preset conan-release -j24
cmake --build ./build --preset conan-debug -j24
```

