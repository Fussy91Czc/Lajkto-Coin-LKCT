// Lajkto genesis transaction generator and consensus monetary-policy self-test.
// This utility needs only a PUBLIC Lajkto address. It never handles wallet secrets.

#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

#include "crypto/crypto.h"
#include "crypto/hash.h"
#include "cryptonote_basic/cryptonote_basic_impl.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "cryptonote_core/cryptonote_tx_utils.h"
#include "string_tools.h"

namespace
{
  bool reward_for(uint64_t already_generated, uint64_t& reward)
  {
    return cryptonote::get_block_reward(0, 0, already_generated, reward, 16);
  }

  int run_consensus_self_test()
  {
    static_assert(MONEY_SUPPLY == LAJKTO_FOUNDER_ALLOCATION + LAJKTO_MINING_SUPPLY,
      "Lajkto supply constants do not add up");

    uint64_t reward = 0;
    if (!cryptonote::get_block_reward(0, 0, 0, reward, 1) || reward != LAJKTO_FOUNDER_ALLOCATION)
    {
      std::cerr << "FAIL genesis founder allocation: " << reward << "\n";
      return 10;
    }

    if (!reward_for(LAJKTO_FOUNDER_ALLOCATION, reward) || reward != LAJKTO_INITIAL_BLOCK_REWARD)
    {
      std::cerr << "FAIL first mining reward: " << reward << "\n";
      return 11;
    }

    const uint64_t first_era_emission = LAJKTO_INITIAL_BLOCK_REWARD * LAJKTO_HALVING_INTERVAL;
    if (!reward_for(LAJKTO_FOUNDER_ALLOCATION + first_era_emission - LAJKTO_INITIAL_BLOCK_REWARD, reward)
        || reward != LAJKTO_INITIAL_BLOCK_REWARD)
    {
      std::cerr << "FAIL reward before first halving: " << reward << "\n";
      return 12;
    }

    if (!reward_for(LAJKTO_FOUNDER_ALLOCATION + first_era_emission, reward)
        || reward != (LAJKTO_INITIAL_BLOCK_REWARD >> 1))
    {
      std::cerr << "FAIL first post-halving reward: " << reward << "\n";
      return 13;
    }

    uint64_t generated = LAJKTO_FOUNDER_ALLOCATION;
    uint64_t expected_reward = LAJKTO_INITIAL_BLOCK_REWARD;
    uint64_t eras = 0;

    while (expected_reward > 0)
    {
      if (!reward_for(generated, reward) || reward != expected_reward)
      {
        std::cerr << "FAIL era " << eras << ": expected " << expected_reward
                  << ", got " << reward << "\n";
        return 14;
      }

      const uint64_t era_emission = expected_reward * LAJKTO_HALVING_INTERVAL;
      if (generated + era_emission > MONEY_SUPPLY)
      {
        std::cerr << "FAIL era emission exceeds max supply\n";
        return 15;
      }

      generated += era_emission;
      expected_reward >>= 1;
      ++eras;
    }

    const uint64_t final_remainder = MONEY_SUPPLY - generated;
    if (!reward_for(generated, reward) || reward != final_remainder)
    {
      std::cerr << "FAIL final rounding remainder: expected " << final_remainder
                << ", got " << reward << "\n";
      return 16;
    }

    generated += reward;
    if (generated != MONEY_SUPPLY)
    {
      std::cerr << "FAIL final supply: " << generated << "\n";
      return 17;
    }

    if (!reward_for(generated, reward) || reward != 0)
    {
      std::cerr << "FAIL emission did not stop at max supply: " << reward << "\n";
      return 18;
    }

    std::cout << "LAJKTO_CONSENSUS_SELF_TEST=PASS\n"
              << "FOUNDER_ALLOCATION_ATOMIC=" << LAJKTO_FOUNDER_ALLOCATION << "\n"
              << "INITIAL_REWARD_ATOMIC=" << LAJKTO_INITIAL_BLOCK_REWARD << "\n"
              << "HALVING_INTERVAL=" << LAJKTO_HALVING_INTERVAL << "\n"
              << "POSITIVE_REWARD_ERAS=" << eras << "\n"
              << "FINAL_REMAINDER_ATOMIC=" << final_remainder << "\n"
              << "MAX_SUPPLY_ATOMIC=" << MONEY_SUPPLY << "\n";
    return 0;
  }
}

int main(int argc, char** argv)
{
  if (argc == 2 && std::string(argv[1]) == "--self-test")
    return run_consensus_self_test();

  if (argc == 2 && std::string(argv[1]) == "--print-mainnet-genesis-hash")
  {
    cryptonote::block genesis{};
    if (!cryptonote::generate_genesis_block(genesis, config::GENESIS_TX, config::GENESIS_NONCE))
    {
      std::cerr << "Failed to construct configured mainnet genesis block\n";
      return 20;
    }
    std::cout << epee::string_tools::pod_to_hex(cryptonote::get_block_hash(genesis)) << "\n";
    return 0;
  }

  if (argc != 4 || std::string(argv[1]) != "--founder-address" ||
      std::string(argv[3]) != "--confirm-personal-allocation")
  {
    std::cerr << "Usage: lajkto-gen-genesis --founder-address <mainnet-public-address> "
                 "--confirm-personal-allocation | --self-test | --print-mainnet-genesis-hash\n";
    std::cerr << "The genesis destination is the founder's personal self-custody allocation, "
                 "not a project treasury or customer wallet.\n";
    return 1;
  }

  const std::string founder_address = argv[2];
  cryptonote::address_parse_info info{};
  if (!cryptonote::get_account_address_from_str(info, cryptonote::MAINNET, founder_address))
  {
    std::cerr << "Invalid Lajkto mainnet address\n";
    return 2;
  }
  if (info.is_subaddress || info.has_payment_id)
  {
    std::cerr << "Genesis destination must be a standard address\n";
    return 3;
  }

  // Genesis must be byte-for-byte reproducible. Ordinary miner transactions use
  // a random transaction key, so derive a public, deterministic transaction key
  // from a domain-separated hash of the personal founder address instead.
  const std::string key_domain = std::string("Lajkto deterministic genesis tx key v1|") + founder_address;
  const crypto::hash key_hash = crypto::cn_fast_hash(key_domain.data(), key_domain.size());
  crypto::secret_key recovery_key{};
  static_assert(sizeof(recovery_key.data) == sizeof(key_hash.data), "unexpected crypto key size");
  std::memcpy(recovery_key.data, key_hash.data, sizeof(recovery_key.data));

  crypto::public_key deterministic_tx_pub{};
  crypto::secret_key deterministic_tx_key{};
  crypto::generate_keys(deterministic_tx_pub, deterministic_tx_key, recovery_key, true);

  cryptonote::transaction tx{};
  if (!cryptonote::construct_miner_tx(
        0, 0, 0, 0, 0,
        info.address,
        tx,
        cryptonote::blobdata(),
        1,
        1,
        &deterministic_tx_key))
  {
    std::cerr << "Failed to construct genesis miner transaction\n";
    return 4;
  }

  const uint64_t amount = cryptonote::get_outs_money_amount(tx);
  if (amount != LAJKTO_FOUNDER_ALLOCATION)
  {
    std::cerr << "Unexpected genesis amount: " << amount << " atomic units\n";
    return 5;
  }

  const cryptonote::blobdata blob = cryptonote::tx_to_blob(tx);
  std::cout << epee::string_tools::buff_to_hex_nodelimer(blob) << "\n";
  return 0;
}
