# pylint: disable=missing-docstring
from conans import ConanFile, CMake


class LibDABIPConan(ConanFile):
    name = 'libdabip'
    version = '1.0.2'
    description = (
        'The DAB IP encoding/decoding infrastructure of the ODR DAB data '
        'toolkit, that provides types and functions to wrap IP datagrams for '
        'transmission and unwrap received datagrams'
    )
    settings = (
        'arch',
        'build_type',
        'compiler',
        'os',
    )
    options = {
        'shared': [True, False],
        'test': [True, False],
    }
    default_options = (
        'shared=True',
        'test=True',
    )
    url = 'https://github.com/Opendigitalradio/libdabip.git'
    license = 'BSD 3-clause'
    exports_sources = (
        'CMakeLists.txt',
        'LICENSE',
        'README.md',
        'cmake/*',
        'include/*',
        'src/*',
        'test/*',
    )

    def build(self):
        cmake = CMake(self, parallel=True)
        cmake.definitions['EXTERNAL_DEPS_VIA'] = 'conan'
        cmake.definitions['DABIP_ENABLE_TESTS'] = (
            'On' if self.options.test
            else 'Off'
        )
        cmake.configure()
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = [
            'dabip'
        ]
        self.cpp_info.includedirs = [
            'include'
        ]

    def requirements(self):
        self.requires('libdabcommon/[>=1.0]@Opendigitalradio/stable')
        if self.options.test:
            self.requires('CUTEX/[>=1.0]@fmorgner/stable')
