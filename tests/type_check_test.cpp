#include "ast.hpp"
#include "compiler.hpp"

#include <catch2/catch.hpp>

auto parse_and_type_check(eml::Compiler& compiler, std::string_view s)
{
  return eml::parse(s).and_then(
      [&compiler](auto&& ast) { return compiler.type_check(ast); });
}

TEST_CASE("Type check on unary expressions")
{
  eml::Compiler compiler;

  GIVEN("- 2")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "-2");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Number` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::NumberType{}));
        }
      }
    }
  }

  GIVEN("(! 2)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "!2");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }
}

TEST_CASE("Type check on binary arithmatic expressions")
{
  eml::Compiler compiler;

  GIVEN("(+ 1 1)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 + 1");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Number` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::NumberType{}));
        }
      }
    }
  }

  GIVEN("(+ 1 true)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 + true");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }

  GIVEN("(* 1 1)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 * 1");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Number` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::NumberType{}));
        }
      }
    }
  }

  GIVEN("(/ true 3)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "true / 3");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }
}

TEST_CASE("Type check on binary comparison expressions")
{
  eml::Compiler compiler;

  GIVEN("(== 1 1)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 == 1");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Bool` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::BoolType{}));
        }
      }
    }
  }

  GIVEN("(== true false)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "true == false");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Bool` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::BoolType{}));
        }
      }
    }
  }

  GIVEN("(== 1 true)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 == true");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }

  GIVEN("(!= 1 1)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 != 1");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Bool` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::BoolType{}));
        }
      }
    }
  }

  GIVEN("(!= 1 true)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 != true");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }

  GIVEN("(< 1 1)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 < 1");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Bool` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::BoolType{}));
        }
      }
    }
  }

  GIVEN("(< true true)")
  {

    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "true < true");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }

  GIVEN("(<= 1 1)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 <= 1");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Bool` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::BoolType{}));
        }
      }
    }
  }

  GIVEN("(<= true true)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "true <= true");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }

  GIVEN("(> 1 1)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 > 1");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Bool` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::BoolType{}));
        }
      }
    }
  }

  GIVEN("(>= 1 1)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "1 >= 1");
      THEN("Passes the type check")
      {
        REQUIRE(checked_ast.has_value());

        THEN("Gets `Bool` as its type")
        {
          const auto& expr = dynamic_cast<eml::ast::Expr&>(**checked_ast);
          REQUIRE(eml::match(expr.type(), eml::BoolType{}));
        }
      }
    }
  }

  GIVEN("(>= true true)")
  {
    WHEN("Type check")
    {
      const auto checked_ast = parse_and_type_check(compiler, "true >= true");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }
}

TEST_CASE("Correctly type infer the let declerations and identifiers")
{
  constexpr auto s1 = "let x = true";
  GIVEN(s1)
  {
    eml::Compiler compiler;

    THEN("Type check should resolve the right hand side to type Bool")
    {
      const auto result = parse_and_type_check(compiler, s1);
      REQUIRE(result);
      const auto bind_type =
          dynamic_cast<eml::ast::Definition&>(**result).binding_type();
      REQUIRE(bind_type.has_value());
      REQUIRE(eml::match(*bind_type, eml::BoolType{}));

      const auto result2 = parse_and_type_check(compiler, "x");
      REQUIRE(result2.has_value());

      const auto& id = dynamic_cast<eml::ast::IdentifierExpr&>(**result2);

      REQUIRE(id.has_type());
      REQUIRE(eml::match(id.type(), eml::BoolType{}));
    }
  }
}

TEST_CASE("Type check for branches")
{
  eml::Compiler compiler;
  GIVEN("An if expression")
  {
    WHEN("Type check")
    {
      const auto checked_ast =
          parse_and_type_check(compiler, "if (true) { 2 } else {3}");
      THEN("Resolve to the type of the branches")
      {
        REQUIRE(checked_ast.has_value());
        const auto& if_expr = dynamic_cast<eml::ast::IfExpr&>(**checked_ast);
        REQUIRE(eml::match(if_expr.type(), if_expr.If().type()));
        REQUIRE(eml::match(if_expr.type(), if_expr.Else().type()));
      }
    }
  }

  GIVEN("A mistyped if expression condition")
  {
    WHEN("Type check")
    {
      const auto checked_ast =
          parse_and_type_check(compiler, "if (1) { 2 } else {3}");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }

  GIVEN("Mismatched if expression branches")
  {
    WHEN("Type check")
    {
      const auto checked_ast =
          parse_and_type_check(compiler, "if (1) { 2 } else {()}");
      THEN("Failed the type check")
      {
        REQUIRE(!checked_ast.has_value());
      }
    }
  }
}
