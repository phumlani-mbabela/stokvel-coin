#include <eosio/eosio.hpp>
using namespace eosio;

CONTRACT bank : public contract {
   public:
      using contract::contract;

      ACTION hi( name nm );

      using hi_action = action_wrapper<"hi"_n, &bank::hi>;
};