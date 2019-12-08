#include "./liboptparse/program_info.hh"

ProgramInfo::ProgramInfo() {
}

ProgramInfo::ProgramInfo(const std::string& name)
    : program_help(),
      program_name(name),
      program_version() { }

ProgramInfo::ProgramInfo(const std::string& name,
                                  const std::string& help)
    : program_help(help),
      program_name(name),
      program_version() { }

ProgramInfo::ProgramInfo(const std::string& name,
                         const std::string& help,
                         const std::string& version)
    : program_help(help),
      program_name(name),
      program_version(version) { }

ProgramInfo::ProgramInfo(const ProgramInfo& program_info)
    : program_help(program_info.program_help),
      program_name(program_info.program_name),
      program_version(program_info.program_version) { }

ProgramInfo::~ProgramInfo() { }
