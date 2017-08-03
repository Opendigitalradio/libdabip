# pylint: disable=missing-docstring
from conans import ConanFile, CMake


class LibDABIPConan(ConanFile):
    name = 'libdabip'
    description = 'The IP handling layer of the ODR DAB data toolkit'
    license = 'BSD 3-clause'
    version = '1.0.1'
    url = 'https://github.com/Opendigitalradio/libdabip.git'
    settings = ['os', 'compiler', 'build_type', 'arch']
    options = {'test': [True, False], 'shared': [True, False]}
    default_options = 'test=False', 'shared=True'
    exports_sources = ('*', '!.git/*', '!build/*')

    def build(self):
        cmake = CMake(self)
        lib = '-DBUILD_SHARED_LIBS=%s' % ('On' if self.options.shared else 'Off')
        args = [lib, '-DCMAKE_INSTALL_PREFIX="%s"' % self.package_folder]
        self.run('cmake %s %s %s'
                 % (self.source_folder,
                    cmake.command_line,
                    ' '.join(args)))
        self.run('cmake --build . --target install %s' % cmake.build_config)

    def package_info(self):
        self.cpp_info.libs = ['dabip']

    def requirements(self):
        if self.options.test:
            self.requires('CUTEX/[>=1.0]@fmorgner/stable')
        self.requires('libdabcommon/[>=1.0]@fmorgner/stable')
