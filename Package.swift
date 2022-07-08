// swift-tools-version: 5.6
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "filament_swift",
    products: [
        .library(
            name: "Filament",
            targets: ["Filament"]),
    ],
    dependencies: [
        .package(url: "https://github.com/Stefterv/filament", exact: "1.25.0")
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
