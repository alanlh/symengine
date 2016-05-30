#include "catch.hpp"
#include <iostream>

#include <symengine/basic.h>
#include <symengine/fields.h>
#include <symengine/symengine_rcp.h>
#include <symengine/dict.h>

using SymEngine::RCP;
using SymEngine::GaloisField;
using SymEngine::gf;
using SymEngine::integer_class;
using SymEngine::map_uint_mpz;

using namespace SymEngine::literals;

TEST_CASE("GaloisField : Basic", "[basic]")
{
    RCP<const GaloisField> r1, r2, r3, r4;
    std::vector<integer_class> a = {2, 3, 4};
    std::vector<integer_class> b = {3, 3, 6, 6};
    r1 = gf(a, 5_z);
    r2 = gf(b, 5_z);
    unsigned int k = 0;
    // std::cout << *r1 << "\n";
    map_uint_mpz mp = r1->dict_;
    REQUIRE(mp[0] == 2);
    REQUIRE(mp[1] == 3);
    REQUIRE(mp[2] == 4);
    // std::cout << *r2 << "\n";
    mp = r2->dict_;
    REQUIRE(mp[0] == 3);
    REQUIRE(mp[1] == 3);
    REQUIRE(mp[2] == 1);
    REQUIRE(mp[3] == 1);
    r3 = r1->gf_add(r2);
    mp = r3->dict_;
    REQUIRE(mp[1] == 1);
    REQUIRE(mp[3] == 1);
    r3 = r1->gf_sub(r2);
    mp = r3->dict_;
    REQUIRE(mp[0] == 4);
    REQUIRE(mp[2] == 3);
    REQUIRE(mp[3] == 4);
    r3 = r1->gf_mul(r2);
    mp = r3->dict_;
    REQUIRE(mp[0] == 1);
    REQUIRE(mp[2] == 3);
    REQUIRE(mp[3] == 2);
    REQUIRE(mp[4] == 2);
    REQUIRE(mp[5] == 4);

    a = {};
    r1 = gf(a, 11_z);
    r2 = r1->gf_neg();
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = r1->gf_add_ground(0_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = r1->gf_sub_ground(0_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = r1->gf_add_ground(3_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 3);
    r2 = r1->gf_sub_ground(3_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 8);
    r2 = r1->gf_mul_ground(0_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = r1->gf_mul_ground(3_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = gf(a, 11_z);
    r3 = r1->gf_add(r2);
    mp = r3->dict_;
    REQUIRE(mp.empty());
    r3 = r1->gf_sub(r2);
    mp = r3->dict_;
    REQUIRE(mp.empty());
    a = {2};
    r2 = gf(a, 11_z);
    r3 = r1->gf_add(r2);
    mp = r3->dict_;
    REQUIRE(mp[0] == 2);
    r3 = r1->gf_sub(r2);
    mp = r3->dict_;
    REQUIRE(mp[0] == 9);
    r2 = r1->gf_quo_ground(3_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());

    a = {1};
    r1 = gf(a, 11_z);
    r2 = r1->gf_neg();
    mp = r2->dict_;
    REQUIRE(mp[0] == 10);
    r2 = r1->gf_add_ground(10_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = r1->gf_add_ground(4_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 5);
    r2 = r1->gf_sub_ground(1_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = r1->gf_sub_ground(4_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 8);
    r2 = r1->gf_mul_ground(0_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = r1->gf_mul_ground(3_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 3);
    r2 = r1->gf_quo_ground(3_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 4);

    a = {1, 2, 3};
    r1 = gf(a, 11_z);
    r2 = r1->gf_neg();
    mp = r2->dict_;
    REQUIRE(mp[0] == 10);
    REQUIRE(mp[1] == 9);
    REQUIRE(mp[2] == 8);
    r2 = r1->gf_add_ground(4_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 5);
    REQUIRE(mp[1] == 2);
    REQUIRE(mp[2] == 3);
    r2 = r1->gf_sub_ground(1_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 0);
    REQUIRE(mp[1] == 2);
    REQUIRE(mp[2] == 3);
    r2 = r1->gf_mul_ground(0_z);
    mp = r2->dict_;
    REQUIRE(mp.empty());
    r2 = r1->gf_mul_ground(7_z);
    mp = r2->dict_;
    REQUIRE(mp[0] == 7);
    REQUIRE(mp[1] == 3);
    REQUIRE(mp[2] == 10);

    a = {3, 2, 1};
    b = {8, 9, 10};
    r1 = gf(a, 11_z);
    r2 = gf(b, 11_z);
    mp = r1->gf_sub(r2)->dict_;
    REQUIRE(mp[0] == 6);
    REQUIRE(mp[1] == 4);
    REQUIRE(mp[2] == 2);
    a = {3, 0, 0, 6, 1, 2};
    b = {4, 0, 1, 0};
    r1 = gf(a, 11_z);
    r2 = gf(b, 11_z);
    mp = r1->gf_mul(r2)->dict_;
    REQUIRE(mp[0] == 1);
    REQUIRE(mp[1] == 0);
    REQUIRE(mp[2] == 3);
    REQUIRE(mp[3] == 2);
    REQUIRE(mp[4] == 4);
    REQUIRE(mp[5] == 3);
    REQUIRE(mp[6] == 1);
    REQUIRE(mp[7] == 2);
    REQUIRE(mp[8] == 0);

    a = {0, 1, 2, 3, 4, 5};
    b = {0, 3, 2, 1};
    r1 = gf(a, 7_z);
    r2 = gf(b, 7_z);
    r1->gf_div(r2, outArg(r3), outArg(r4));
    mp = r3->dict_;
    REQUIRE(mp[0] == 0);
    REQUIRE(mp[1] == 1);
    REQUIRE(mp[2] == 5);
    mp = r4->dict_;
    REQUIRE(mp[0] == 0);
    REQUIRE(mp[1] == 1);
    REQUIRE(mp[2] == 6);
    REQUIRE(eq(*r3, *(r1->gf_quo(r2))));

    a = {0, 1, 2, 3, 4, 5};
    b = {3, 2, 1};
    r1 = gf(a, 7_z);
    r2 = gf(b, 7_z);
    r1->gf_div(r2, outArg(r3), outArg(r4));
    mp = r3->dict_;
    REQUIRE(mp[0] == 6);
    REQUIRE(mp[1] == 0);
    REQUIRE(mp[2] == 1);
    REQUIRE(mp[3] == 5);
    mp = r4->dict_;
    REQUIRE(mp[0] == 3);
    REQUIRE(mp[1] == 3);
    REQUIRE(eq(*r3, *(r1->gf_quo(r2))));

    a = {1};
    b = {3, 2, 1};
    r1 = gf(a, 7_z);
    r2 = gf(b, 7_z);
    r1->gf_div(r2, outArg(r3), outArg(r4));
    REQUIRE(r3->dict_.empty());
    mp = r4->dict_;
    REQUIRE(mp[0] == 1);
}
