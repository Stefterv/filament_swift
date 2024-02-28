# Filament Swift

Swift bindings and Swift Package Manager package for [Filament](https://github.com/google/filament)

## Installation

### Xcode

Select File -> Swift Packages -> Add Package Dependency and enter https://github.com/Stefterv/filament_swift/

## Development

Clone the repo and run
```
$ ./release.sh

```
To update the filament c++ library to the latest version edit the `$VERSION` variable in `release.sh` to the latest version and re-run 
```
$ ./release.sh

```

If the command release fails to run, delete the `filament/out` folder to reset and build from scratch
