# LKCT: planned monetary policy, staking and difficulty update

Proposal date: 17 November 2026

Status: in development; not activated

We are preparing a coordinated LKCT update. Its goals are faster difficulty adjustment when mining power changes, voluntary fixed-term staking, and long-term miner rewards. LKCT will continue to use its own blockchain, Proof of Work and RandomX. The target block interval remains 60 seconds. The update is intended to preserve the existing chain and its history, without launching a new blockchain.

## What we plan and why

### Faster difficulty adjustment

The current calculation uses a 720-block window. The experimental implementation being prepared works with approximately 60 blocks so that the network can respond faster when miners join or leave. The aim is to reduce prolonged swings in block intervals. This does not shorten the one-minute target interval.

Stability, timestamp-manipulation and reorganization tests must be completed before deployment. Historical blocks before activation will continue to be validated under the original rules.

### Voluntary fixed-term staking

| Lock period | Total reward for the agreed term |
|---|---:|
| 30 days | 1% |
| 90 days | 3% |
| 180 days | 5% |
| 365 days | 10% |

These percentages apply to the whole term, not to an annual rate. Early withdrawal returns the principal without any reward; any transaction fee is accounted for at withdrawal.

Staking will be funded by a separate additional issuance reserve of at most 200 million LKCT. The reward is reserved when a deposit is accepted. New commitments cannot be accepted without sufficient available reserve. Early withdrawal releases the unpaid reserved reward.

Staking will not replace mining or validate blocks instead of PoW. Returning the principal will not issue new coins. The proposed format makes deposit principal, term and withdrawal amounts public; it is not anonymous staking.

### Separate issuance accounting and long-term miner rewards

The original founder allocation of 15 million LKCT and mining allocation of 85 million LKCT will remain unchanged, as will the original halving every 2,125,000 blocks. The staking reserve will not be deducted from the mining allocation.

Only after the original 85 million LKCT mining allocation has been exactly exhausted is a permanent security reward of 0.75 LKCT per block intended to begin, without further halvings. It is meant to maintain ongoing miner incentives; the reward alone does not guarantee sufficient network security.

At most 300 million LKCT can be issued before this permanent emission is counted. Unissued staking reserve is not circulating supply. Total future supply will not have a fixed 300-million cap, because the subsequent security emission is intended to continue permanently.

## Planned activation

The preparatory target is **block 100,000**. Based on the height checked on 17 November 2026 and an average of 60 seconds per block, this corresponded roughly to **10 December 2026**. The jointly confirmed height will be decisive; the calendar estimate can change with mining speed.

We plan at least 14 days to distribute the completed update before activation. If the lead time cannot be met, implementation and testing remain incomplete, or participant coordination cannot be confirmed, a later height will be selected before final deployment.

**The 0.75 LKCT reward will not automatically start at block 100,000.** It remains conditional on exhaustion of the original mining issuance.

## Pools, nodes and current status

This consensus change requires a coordinated hard fork. Updated nodes and pools must use identical rules and the same activation height. After activation, old nodes may reject new blocks and continue on an incompatible branch.

VeinPool compatibility must be confirmed before deployment, and updates must be coordinated with other known participants. VeinPool compatibility has not yet been confirmed.

The production network has not been changed by this update. Component tests for issuance accounting, database operations, deposit funding and signatures have passed. Full staking integration into the blockchain and wallets, network tests, audits and final deployment packages are not yet complete.

This announcement describes a plan. It does not confirm that staking has launched or that the activation date is final. The final version, activation height and operator instructions will be published separately once preparation is complete.
