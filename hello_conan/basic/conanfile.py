from conans import ConanFile, CMake

class HellobasicConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "nlohmann_json/3.9.1", "fmt/7.1.2" # [requires], comma-separated list
   generators = "cmake"                          # [generators]
   default_options = ""

   def imports(self):
      self.output.info      ("imports() running, white [info]")
      self.output.success   ("imports() running, green [success]")
      self.output.warn      ("imports() running, yellow [warn]")
      self.output.error     ("imports() running, red [error]")
   def build(self):
      self.output.info("build() running")
      cmake = CMake(self)
      cmake.configure()
      cmake.build()