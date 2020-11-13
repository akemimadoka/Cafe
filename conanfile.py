from conans import ConanFile, CMake, tools

LibList = [("Encoding", "CAFE_INCLUDE_ENCODING"), ("Environment", "CAFE_INCLUDE_ENVIRONMENT"),
           ("ErrorHandling", "CAFE_INCLUDE_ERROR_HANDLING"), ("Io", "CAFE_INCLUDE_IO"), ("TextUtils", "CAFE_INCLUDE_TEXT_UTILS")]

Options = [
    # Cafe
    ("CAFE_INCLUDE_TESTS", [True, False], False),

    # Cafe.Encoding
    ("CAFE_ENCODING_INCLUDE_ENCODING_LIST", "ANY", "UTF-8;UTF-16;UTF-32;GB2312"),
    ("CAFE_ENCODING_INCLUDE_UNICODE_DATA", [True, False], True),
    ("CAFE_ENCODING_INCLUDE_RUNTIME_ENCODING", [True, False], True),

    # Cafe.Encoding.UnicodeData
    ("CAFE_ENCODING_UNICODE_DATA_INCLUDE_RUNTIME", [True, False], True),
    ("CAFE_ENCODING_UNICODE_DATA_INCLUDE_COMPILE_TIME", [True, False], False),

    # Cafe.ErrorHandling
    ("CAFE_ERROR_HANDLING_INCLUDE_STACKWALKER", [True, False], False),
    ("CAFE_ERROR_HANDLING_ENABLE_STACKWALKER_IN_CAFE_EXCEPTION",
     [True, False], False),

    # Cafe.Io
    ("CAFE_IO_INCLUDE_STREAMS", [True, False], True),
    ("CAFE_IO_INCLUDE_STREAM_HELPERS", [True, False], True),

    # Cafe.Io.Streams
    ("CAFE_IO_STREAMS_USE_CONCEPTS", [True, False], True),
    ("CAFE_IO_STREAMS_INCLUDE_FILE_STREAM", [True, False], True),
    ("CAFE_IO_STREAMS_FILE_STREAM_ENABLE_FILE_MAPPING", [True, False], True),

    # Cafe.TextUtils
    ("CAFE_INCLUDE_TEXT_UTILS_MISC", [True, False], True),
    ("CAFE_INCLUDE_TEXT_UTILS_FORMAT", [True, False], True),
    ("CAFE_INCLUDE_TEXT_UTILS_STREAM_HELPERS", [True, False], True)
]

class CafeConan(ConanFile):
    name = "Cafe"
    version = "0.1"
    license = "MIT"
    author = "akemimadoka <chino@hotococoa.moe>"
    url = "https://github.com/akemimadoka/Cafe"
    description = "A general purpose C++ library"
    topics = ("C++")
    settings = "os", "compiler", "build_type", "arch"

    options = {"shared": [True, False]}
    options.update({"include_%s" % lib[0]: [True, False] for lib in LibList})
    options.update({opt[0]: opt[1] for opt in Options})

    default_options = ["shared=False"]
    default_options.extend(["include_%s=True" % lib[0] for lib in LibList])
    default_options.extend(["{}={}".format(opt[0], opt[2]) for opt in Options])
    default_options = tuple(default_options)

    generators = "cmake"

    exports_sources = ("CMakeLists.txt", "License", "Cafe.Core*", "Cafe.Encoding*", "Cafe.Environment*",
        "Cafe.ErrorHandling*", "Cafe.Io*", "Cafe.TextUtils*")

    def requirements(self):
        if self.options.CAFE_INCLUDE_TESTS:
            self.requires("catch2/3.0.0@catchorg/stable")

    def configure_cmake(self):
        cmake = CMake(self)
        for lib in LibList:
            cmake.definitions[lib[1]] = getattr(
                self.options, "include_%s" % lib[0])
        for opt in Options:
            cmake.definitions[opt[0]] = getattr(self.options, opt[0])
        cmake.configure()
        return cmake

    def build(self):
        if self.settings.compiler == 'Visual Studio':
            with tools.vcvars(self.settings, filter_known_paths=False):
                cmake = self.configure_cmake()
                cmake.build()
        else:
            cmake = self.configure_cmake()
            cmake.build()

    def package(self):
        if self.settings.compiler == 'Visual Studio':
            with tools.vcvars(self.settings, filter_known_paths=False):
                cmake = self.configure_cmake()
                cmake.install()
        else:
            cmake = self.configure_cmake()
            cmake.install()

    def package_info(self):
        #self.cpp_info.libs = tools.collect_libs(self)
        self.cpp_info.libs = ["Cafe.Encoding.RuntimeEncoding", "Cafe.Encoding.UnicodeData",
                              "Cafe.Environment", "Cafe.Io.Streams", "Cafe.ErrorHandling"]
