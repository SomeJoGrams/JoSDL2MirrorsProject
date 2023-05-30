# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/io
    REF boost-1.82.0
    SHA512 af3b8e922369f8e09f5fd3d91c7bb1ef2b3697199f118a43f1e283dc2675f126994114d11aef531d9d2c63feb070183e7d43a5ce56f6e81b875a29e3ae358814
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})