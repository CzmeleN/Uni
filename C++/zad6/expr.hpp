#pragma once

#include <string>
#include <vector>

namespace expression_tree {

class expr {
public:
    expr() = default;
    virtual ~expr() = default;

    expr(const expr&) = delete;
    expr& operator=(const expr&) = delete;
    expr(expr&&) = delete;
    expr& operator=(expr&&) = delete;

    virtual bool calc() const = 0;
    virtual std::string print() const = 0;
    virtual int get_prio() const = 0;
};

class lit final : public expr {
private:
    const bool val;
public:
    static lit TRUE;
    static lit FALSE;

    lit(bool v);

    bool calc() const override;
    std::string print() const override;
    int get_prio() const override;
};

class var final : public expr {
private:
    std::string name;
    static std::vector<std::pair<std::string, bool>> vars;

public:
    var(std::string n);

    bool calc() const override;
    std::string print() const override;
    int get_prio() const override;

    static void add(const std::string &n, bool v);
    static void rm(const std::string& n);
    static void set(const std::string& n, bool v);
};

class uop : public expr {
protected:
    expr* child;
public:
    uop(expr* c);
    ~uop();
};

class bop: public expr {
protected:
    expr *left, *right;
public:
    bop(expr* l, expr* r);
    ~bop();

    std::string print_child(expr* child, bool is_right) const;
};

class not_op final : public uop {
public:
    using uop::uop;

    bool calc() const override;
    std::string print() const override;
    int get_prio() const override;
};

class and_op final : public bop {
public:
    using bop::bop;

    bool calc() const override;
    std::string print() const override;
    int get_prio() const override;
};

class xor_op final : public bop {
public:
    using bop::bop;

    bool calc() const override;
    std::string print() const override;
    int get_prio() const override;
};

class or_op final : public bop {
public:
    using bop::bop;

    bool calc() const override;
    std::string print() const override;
    int get_prio() const override;
};

class imp_op final : public bop {
public:
    using bop::bop;

    bool calc() const override;
    std::string print() const override;
    int get_prio() const override;
};

class eqv_op final : public bop {
public:
    using bop::bop;

    bool calc() const override;
    std::string print() const override;
    int get_prio() const override;
};

}
