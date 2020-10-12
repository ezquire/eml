#include <ApprovalTests.hpp>
#include <catch2/catch.hpp>

#include "debug.hpp"
#include "eml.hpp"

namespace {
enum class ForDocumentation { no, yes };

void verify_eml(const std::string_view source,
                ForDocumentation for_documentation = ForDocumentation::no)
{
  eml::GarbageCollector gc{};

  eml::CompilerConfig config = {eml::SameScopeShadowing::allow};
  eml::Compiler compiler{gc, config};
  eml::VM vm{gc};

  std::stringstream ss;
  ss << "Input:\n";
  if (for_documentation == ForDocumentation::yes) {
    ss << "```eml\n";
  }
  ss << source << '\n';
  if (for_documentation == ForDocumentation::yes) {
    ss << "```";
  }
  ss << '\n';

  if (!source.empty()) {
    eml::parse(source, gc)
        .and_then([&](std::unique_ptr<eml::AstNode>&& ast) {
          if (for_documentation == ForDocumentation::no) {
            ss << "Parse into:\n" << eml::to_string(*ast) << "\n\n";
          }
          return compiler.type_check(ast);
        })
        .map([&](auto ast) { return compiler.generate_code(*ast); })
        .map([&](auto tuple) {
          const auto& [bytecode, type] = tuple;

          if (for_documentation == ForDocumentation::no) {
            ss << "Compile into:\n" << bytecode.disassemble() << '\n';
          }

          const auto result = vm.interpret(bytecode);
          REQUIRE(result);
          ss << "Executes to:\n";
          if (for_documentation == ForDocumentation::yes) {
            ss << "```\n";
          }
          ss << eml::to_string(type, *result) << '\n';
          if (for_documentation == ForDocumentation::yes) {
            ss << "```";
          }
        })
        .map_error([&ss](const auto& errors) {
          ss << "Error message:\n";
          std::for_each(std::begin(errors), std::end(errors),
                        [&ss](auto e) { ss << eml::to_string(e); });
        });

    const auto options = [&]() {
      if (for_documentation == ForDocumentation::yes) {
        return ApprovalTests::Options{}.fileOptions().withFileExtension(
            ".docs.md");
      }
      return ApprovalTests::Options{};
    }();

    ApprovalTests::Approvals::verify(ss.str(), options);
  }
}

void verify_eml_from_file()
{
  auto filename =
      ApprovalTests::Approvals::getDefaultNamer()->getApprovedFile(".eml");
  auto source = ApprovalTests::FileUtils::readFileThrowIfMissing(filename);
  verify_eml(source);
}
} // anonymous namespace

TEST_CASE("If Else Test")
{
  constexpr std::string_view s = "if (5 > 1) {2 + 3} else {4 - 6}";
  verify_eml(s);
  verify_eml(s, ForDocumentation::yes);
}

TEST_CASE("If Else Test 2")
{
  verify_eml_from_file();
}

TEST_CASE("Test Syntax Error")
{
  verify_eml("if (5 > 1 {2 + 3} else {4 - 6}");
}

// TEST_CASE("Test with String")
//{
//  const std::string s = R"("Hello, " ++ "world")";
//  verify_eml(s);
//}
