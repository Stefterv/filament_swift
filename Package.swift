// swift-tools-version: 5.6
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "filament_swift",
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "Filament",
            targets: ["Filament"]),
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.0"),
        .package(url: "https://github.com/Stefterv/filament", branch: "main")
    ],
    targets: [
        .target(
            name: "Filament",
            dependencies: [
                "FilamentBindings"
            ],
            path: "Helpers"
        ),
        .target(
            name: "FilamentBindings",
            dependencies: [
                "filament",
            ],
            path: "Bindings",
            cxxSettings: [
                .headerSearchPath("../include")
            ]
        ),
    ],
    cxxLanguageStandard: .cxx17
)
