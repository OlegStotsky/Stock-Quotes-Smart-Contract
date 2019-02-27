#include <eosiolib/eosio.hpp>

using namespace eosio;

class [[eosio::contract("quoteshashes")]] quoteshashes : public eosio::contract {

public:
  using contract::contract;
  
  quoteshashes(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

  [[eosio::action]]
  void upsert(uint64_t id, std::string hash) {
    quotes_hash_index hashes(_code, _code.value);
    hashes.emplace(_code, [&]( auto& row ) {
      row.id = id;
      row.hash = hash;
    });
  }

private:
  struct [[eosio::table]] quotes_hash {
    uint64_t id;
    std::string hash;
    uint64_t primary_key() const { return id; }
  };
  typedef eosio::multi_index<name("quoteshashes"), quotes_hash> quotes_hash_index;
};

EOSIO_DISPATCH(quoteshashes, (upsert))