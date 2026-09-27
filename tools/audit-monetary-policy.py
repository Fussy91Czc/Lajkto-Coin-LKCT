#!/usr/bin/env python3
"""Independent arithmetic audit of LKCT monetary constants.

This script deliberately does not call get_block_reward(). It parses the
consensus constants and recomputes the halving schedule with Python arbitrary-
precision integers, giving us a second implementation of the supply math.
"""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
CFG = ROOT / "src" / "cryptonote_config.h"
TEXT = CFG.read_text(encoding="utf-8")


def constant(name: str) -> int:
    m = re.search(rf"^#define\s+{re.escape(name)}\s+\(\(uint64_t\)(\d+)(?:ULL)?\)", TEXT, re.M)
    if not m:
        raise SystemExit(f"AUDIT_FAIL missing/unparseable constant {name}")
    return int(m.group(1))


money_supply = constant("MONEY_SUPPLY")
founder = constant("LAJKTO_FOUNDER_ALLOCATION")
mining_supply = constant("LAJKTO_MINING_SUPPLY")
initial_reward = constant("LAJKTO_INITIAL_BLOCK_REWARD")
halving_interval = constant("LAJKTO_HALVING_INTERVAL")
tail = constant("FINAL_SUBSIDY_PER_MINUTE")
coin = constant("COIN")

errors: list[str] = []
if money_supply != founder + mining_supply:
    errors.append("max supply != founder + mining allocation")
if founder != 15_000_000 * coin:
    errors.append("founder allocation is not exactly 15,000,000 LKCT")
if mining_supply != 85_000_000 * coin:
    errors.append("mining allocation is not exactly 85,000,000 LKCT")
if money_supply != 100_000_000 * coin:
    errors.append("maximum supply is not exactly 100,000,000 LKCT")
if initial_reward != 20 * coin:
    errors.append("initial block reward is not exactly 20 LKCT")
if halving_interval != 2_125_000:
    errors.append("halving interval changed")
if tail != 0:
    errors.append("tail emission is not zero")

reward = initial_reward
emitted = 0
eras = []
max_u64 = (1 << 64) - 1
while reward > 0:
    era_emission = reward * halving_interval
    if era_emission > max_u64:
        errors.append("era multiplication exceeds uint64")
    if emitted + era_emission > mining_supply:
        errors.append("full halving era would exceed mining allocation")
        break
    eras.append((len(eras), reward, era_emission))
    emitted += era_emission
    reward >>= 1

remainder = mining_supply - emitted
positive_mining_blocks = len(eras) * halving_interval + (1 if remainder else 0)
final_supply = founder + emitted + remainder

if final_supply != money_supply:
    errors.append("recomputed final supply does not equal MONEY_SUPPLY")
if remainder < 0:
    errors.append("negative final remainder")
if remainder > max_u64:
    errors.append("final remainder exceeds uint64")
if len(eras) != 31:
    errors.append(f"expected 31 positive integer-reward eras, got {len(eras)}")
if remainder != 27_625_000:
    errors.append(f"expected final remainder 27,625,000 atomic units, got {remainder}")

if errors:
    for e in errors:
        print(f"AUDIT_FAIL {e}", file=sys.stderr)
    raise SystemExit(1)

seconds = positive_mining_blocks * 60
years = seconds / (365.2425 * 24 * 3600)
print("LKCT_MONETARY_ARITHMETIC_AUDIT=PASS")
print(f"MAX_SUPPLY_ATOMIC={money_supply}")
print(f"FOUNDER_ATOMIC={founder}")
print(f"MINING_SUPPLY_ATOMIC={mining_supply}")
print(f"INITIAL_REWARD_ATOMIC={initial_reward}")
print(f"HALVING_INTERVAL={halving_interval}")
print(f"FULL_POSITIVE_ERAS={len(eras)}")
print(f"EMITTED_IN_FULL_ERAS_ATOMIC={emitted}")
print(f"FINAL_REMAINDER_ATOMIC={remainder}")
print(f"POSITIVE_MINING_BLOCKS={positive_mining_blocks}")
print(f"APPROX_EMISSION_YEARS_AT_60S={years:.6f}")
print(f"FIRST_ERA_EMISSION_ATOMIC={eras[0][2]}")
print(f"FINAL_SUPPLY_ATOMIC={final_supply}")
