// swift-tools-version: 5.6
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription
let targets = [
    "libbackend","libbasis_transcoder","libcamutils","libcivetweb","libdracodec","libfilabridge","libfilaflat","libfilamat","libfilamat_lite","libfilament-iblprefilter","libfilament","libfilameshio","libgeometry","libgltfio_core","libibl-lite","libibl","libimage","libktxreader","libmeshoptimizer","libmikktspace","libshaders","libsmol-v","libstb","libuberarchive","libuberzlib","libutils","libviewer","libvkshaders","libzstd"
]

let package = Package(
    name: "filament_swift",
    products: [
        .library(
            name: "filament",
            targets: ["FilamentBindings", "Helpers"] + targets),
    ],
    targets: ([
        .target(
            name: "Helpers",
            dependencies: [
                "FilamentBindings"
            ],
            path: "Helpers"
        ),
        .target(
            name: "FilamentBindings",
            path: "Bindings"
        )
    ] + targets.map({ .binaryTarget(name: $0, path: "lib/\($0).xcframework") })),
    cxxLanguageStandard: .cxx17
)
