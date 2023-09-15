#!/bin/bash
set -e

VERSION="1.42.2"
TYPE="release"

if [ ! -d "filament" ]
then
    git clone https://github.com/google/filament.git filament
else
    git -C filament fetch
fi
git -C filament checkout tags/v${VERSION}

filament/build.sh -p ios -i "${TYPE}"

LEADER_PATH="filament/out/ios-${TYPE}/filament/lib/arm64"
OUTPUT_DIR="lib/"

rm -rf "${OUTPUT_DIR}"

# Loop through each file in the leader path. For each library we find, we'll collect additional
# architectures in the other paths and combine them all into a universal library.
for FILE in "${LEADER_PATH}"/*.a; do
    [ -f "${FILE}" ] || continue

    LIBRARY_NAME=$(basename "${FILE%.*}")

    echo "Creating xcframework for library: ${LIBRARY_NAME}"
    INPUT_FILES=("-library ${LEADER_PATH}/${LIBRARY_NAME}.a")

    if [[ $LIBRARY_NAME == "libfilament" ]]; then
        echo "Adding headers for ${LIBRARY_NAME}"
        INPUT_FILES+=("-headers ${LEADER_PATH}../../../include")
    fi

    for ARCH_PATH in "${PATHS[@]:1}"; do
        THIS_FILE="${ARCH_PATH}/${LIBRARY_NAME}.a"
        if [[ -f "${THIS_FILE}" ]]; then
            INPUT_FILES+=(" -library ${THIS_FILE}")
        else
            echo "Error: ${THIS_FILE} does not exist."
            exit 1
        fi
    done

    echo "${INPUT_FILES[@]}"

    eval "xcodebuild -create-xcframework ${INPUT_FILES[@]} -output ${OUTPUT_DIR}/${LIBRARY_NAME}.xcframework"
done