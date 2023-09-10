// swift-tools-version: 5.9
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
            targets: ["Filament"]
        ),
    ],
    targets: ([
        .target(
            name: "Filament",
            dependencies: targets.map({ .byName(name: $0 )}),
            path: "headers",
            swiftSettings: [.interoperabilityMode(.Cxx)]
        )
//        .target(
//            name: "Filament",
//            dependencies: ["Bindings"],
//            path: "Helpers"
//        ),
//        .target(
//            name: "Bindings",
//            dependencies: targets.map({ .byName(name: $0) }),
//            path: "Bindings"
//        )
    ] + targets.map({ .binaryTarget(name: $0, path: "lib/\($0).xcframework") }))
//    cxxLanguageStandard: .gnucxx20,
)
