#ifndef _WGTCC_SCOPE_H_
#define _WGTCC_SCOPE_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>


class Identifier;
class Token;


enum class ScopeType {
  FILE,
  PROTO,
  BLOCK,
  FUNC,
};


class Scope {
  friend class StructType;
  typedef std::vector<Identifier*> TagList;
  typedef std::map<std::string, Identifier*> IdentMap;

public:
  static Scope* New(Scope* parent, ScopeType type);
  ~Scope() {}
  Scope* Parent() { return parent_; }
  void SetParent(Scope* parent) { parent_ = parent; }
  ScopeType Type() const { return type_; }

  Identifier* Find(const Token* tok);
  Identifier* FindInCurScope(const Token* tok);
  Identifier* FindTag(const Token* tok);
  Identifier* FindTagInCurScope(const Token* tok);
  TagList AllTagsInCurScope() const;
  void Insert(Identifier* ident);
  void InsertTag(Identifier* ident);
  void Print();

  bool operator==(const Scope& other) const { return type_ == other.type_; }
  IdentMap::iterator begin() { return identMap_.begin(); }
  IdentMap::iterator end() { return identMap_.end(); }
  size_t size() const { return identMap_.size(); }
  void Insert(const std::string& name, Identifier* ident);

private:
  explicit Scope(Scope* parent, ScopeType type)
      : parent_(parent), type_(type) {}
  
  Identifier* Find(const std::string& name);
  Identifier* FindInCurScope(const std::string& name);
  Identifier* FindTag(const std::string& name);
  Identifier* FindTagInCurScope(const std::string& name);
  std::string TagName(const std::string& name) { return name + "@:tag"; }
  static bool IsTagName(const std::string& name) {
    return name.size() > 5 && name[name.size() - 5] == '@';
  }
  const Scope& operator=(const Scope& other);
  Scope(const Scope& scope);

  Scope* parent_;
  ScopeType type_;
  IdentMap identMap_;
};

#endif
