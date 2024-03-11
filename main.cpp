#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/AST/AST.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchersMacros.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

static llvm::cl::OptionCategory MyToolCategory("My tool options");

class FunctionMatcher : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const FunctionDecl *FuncDecl = Result.Nodes.getNodeAs<FunctionDecl>("function")) {
      // You can access the matched function declaration here
      FuncDecl->dump();
    }
  }
};

struct MyParse : public CommonOptionsParser
{
   MyParse(int& a, const char** b, llvm::cl::OptionCategory& c, llvm::cl::NumOccurrencesFlag d = llvm::cl::OneOrMore, const char* e=nullptr) :
   CommonOptionsParser(a,b,c,d,e) {}
   
};


int main(int argc, const char **argv) {
  MyParse OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

  FunctionMatcher Matcher;
  DeclarationMatcher FunctionDoublePtrMatcher = functionDecl(
      hasAnyParameter(hasType(pointerType(pointee(builtinType()))))
  ).bind("function");

  MatchFinder Finder;
  Finder.addMatcher(FunctionDoublePtrMatcher, &Matcher);

  Tool.run(newFrontendActionFactory(&Finder).get());

  return 0;
}




#if 0

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;

static llvm::cl::OptionCategory MyToolCategory("My tool options");


class FunctionMatcher : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const FunctionDecl *FuncDecl = Result.Nodes.getNodeAs<FunctionDecl>("function")) {
      // You can access the matched function declaration here
      FuncDecl->dump();
    }
  }
};

struct OptionsParserMe : public CommonOptionsParser 
{

OptionsParserMe(int& a, const char**b, llvm::cl::OptionCategory&c, llvm::cl::NumOccurrencesFlag d, const char*e) :
CommonOptionsParser(a,b,c,d,e){}

}

int main(int argc, const char **argv) {
  OptionsParserMe OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

  FunctionMatcher Matcher;
  DeclarationMatcher FunctionDoublePtrMatcher = functionDecl(
      hasAnyParameter(hasType(pointerType(pointee(builtinType()))))
  ).bind("function");

  MatchFinder Finder;
  Finder.addMatcher(FunctionDoublePtrMatcher, &Matcher);

  Tool.run(newFrontendActionFactory(&Finder).get());

  return 0;
}
//#if 0

class FunctionMatcher : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const FunctionDecl *FuncDecl = Result.Nodes.getNodeAs<FunctionDecl>("function")) {
      // You can access the matched function declaration here
      FuncDecl->dump();
    }
  }
};

int main(int argc, const char **argv) {
  if (argc > 1) {
    ClangTool Tool(*argv);
    FunctionMatcher Matcher;
    DeclarationMatcher FunctionDoublePtrMatcher = functionDecl(
        hasAnyParameter(hasType(pointerType(pointee(isSpecificBuiltinType("double")))))
    ).bind("function");

    Tool.run(newFrontendActionFactory(&Matcher).get());

    return 0;
  } else {
    llvm::errs() << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }
}
#endif



