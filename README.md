# Lajkto Coin Technology (LKCT)

Official public repository for **LKCT**, an independent CryptoNote-derived blockchain using RandomX Proof of Work.

[Official website](https://lajkto.eu/lkct/) · [Downloads](https://lajkto.eu/lkct/download.html) · [GitHub Releases](https://github.com/Fussy91Czc/Lajkto-Coin-LKCT/releases) · [Mining pool](https://lajkto.eu/pool/lkct.php) · [Telegram](https://t.me/LajkToOfficial)

## Current release — start here

**24 November 2026:** the official mainnet node runs LKCT **v1.2 r2** (`0.18.5.1-a8f39fef5`). Protocol v17 activates at **block 100,000**. The node is already deployed; the new consensus rules and staking are not yet active.

| I want to… | Where to go |
| --- | --- |
| Run or upgrade a full node | [Production node r2 and verification](docs/lkct-v1.2-r2-production.md) · [Signed operator packages](https://github.com/Fussy91Czc/Lajkto-Coin-LKCT/releases/tag/v1.2-operator-r2) |
| Download or update a wallet | [Current wallet downloads](#wallet-downloads) |
| Install a node inside my wallet | [Wallet-managed installation](docs/lkct-v1.2-r2-production.md#wallet-managed-node-installation) |
| Mine LKCT | [PPLNS / SOLO / mobile mining](#mine-lkct) |
| Operate my own mining pool | [Pool setup kit](pool-r2/README.md) · [CZ](pool-r2/README.cs.md) · [DE](pool-r2/README.de.md) · [ZIP](https://lajkto.eu/lkct/downloads/LKCT-Pool-v1.2-r2-Starter-Kit.zip) |
| Integrate a mining directory | [Public JSON API](https://lajkto.eu/pool/lkct-stats.php) · [Integration guide](https://lajkto.eu/lkct/developers.html#api) |
| Understand consensus and staking | [Monetary policy](#monetary-policy) · [Original v1.2 proposal](docs/lkct-policy-v1.2-plan.md) |
| View project history | [Milestones and historical releases](docs/MILESTONES.md) |

## Wallet downloads

The wallet application and blockchain node have **separate release versions**. The current desktop wallet remains RC5. Android updates must match the installed wallet's signing certificate.

| Platform / signing track | Current offered wallet | Download |
| --- | --- | --- |
| Windows x64 | v1.2-rc5, pack2 | [ZIP](https://lajkto.eu/lkct/downloads/LKCT-Wallet-Windows-x64-v1.2-rc5-pack2.zip) |
| Ubuntu 22.04+ x64 | v1.2-rc5 | [DEB](https://lajkto.eu/lkct/downloads/LKCT-Wallet-v1.2-rc5-Ubuntu22.04-amd64.deb) · [AppImage](https://lajkto.eu/lkct/downloads/LKCT-Wallet-v1.2-rc5-Linux-x86_64.AppImage) |
| Debian 11 Legacy x64 | v1.2-rc5 | [DEB](https://lajkto.eu/lkct/downloads/LKCT-Wallet-v1.2-rc5-Debian11-Legacy-amd64.deb) · [Portable TAR.GZ](https://lajkto.eu/lkct/downloads/LKCT-Wallet-Linux-Legacy-x86_64-v1.2-rc5.tar.gz) |
| Android ARM64, R7/R8/R8a signing track | R13, versionCode 19 | [Official APK update](https://lajkto.eu/lkct/android-wallet-download.php?track=r7) |
| Android ARM64, 22 September signing track | v1.2-rc5 | [Official APK update](https://lajkto.eu/lkct/android-wallet-download.php?track=september) |

[RC5 release and assets on GitHub](https://github.com/Fussy91Czc/Lajkto-Coin-LKCT/releases/tag/v1.2-wallet-rc5) · [RC5 SHA-256 checksums](https://lajkto.eu/lkct/downloads/LKCT-Wallet-v1.2-rc5-SHA256SUMS-2.txt) · [Android signing-aware update feed](https://lajkto.eu/lkct/downloads/android-wallet-updates.json)

The Android R13 first signing track is currently served by the official website; it is not yet a separate GitHub release. R13 for the second signing track remains pending. Physical-device background mining and node hosting have not yet been verified. Do not uninstall an existing wallet to bypass a signature mismatch. Securely back up recovery information before upgrading.

To install and host the signed r2 node inside a compatible wallet, open **Settings → Network & node → Download and install node v1.2**, complete installation, then enable hosting. Activation remains determined by blockchain height, not installation time.

## Mine LKCT

Official RandomX Stratum endpoints:

| Mode | Address |
| --- | --- |
| PPLNS | `stratum+tcp://lajkto.eu:4450` |
| SOLO | `stratum+tcp://lajkto.eu:4451` |
| Mobile PPLNS | `stratum+tcp://lajkto.eu:4452` |

Use your own valid LKCT receiving address with a compatible RandomX miner. For your **own independent pool**, use the [PPLNS/SOLO operator starter kit](pool-r2/README.md), not the production LAJKTO addresses or private configuration. The template starts locally with automated payouts disabled; fresh-host deployment and post-fork payouts still require testing.

## Monetary policy

| Parameter | Before block 100,000 | From block 100,000 |
| --- | --- | --- |
| Founder allocation | 15 million LKCT | Unchanged |
| Original mining allocation | 85 million LKCT | Unchanged |
| Initial mining reward / halving | 20 LKCT / 2,125,000 blocks | Original schedule preserved |
| Target block interval | 60 seconds | 60 seconds |
| Difficulty window | 720 blocks | 60 blocks |
| Voluntary staking reward reserve | Not active | Up to 200 million LKCT |
| Permanent security subsidy | None | 0.75 LKCT/block only after original mining allocation exhaustion |

Precision is eight decimal places. The post-activation staking reward reserve caps reward promises; it is not circulating supply. After permanent security emission starts there is no fixed total supply cap. See [production release and test evidence](docs/lkct-v1.2-r2-production.md) and the [original proposal](docs/lkct-policy-v1.2-plan.md). All operators should upgrade before the fixed activation height. Other operators' upgrade readiness is not guaranteed, and internal engineering tests are not independent certification.

## Repository layout

| Directory / file | Purpose |
| --- | --- |
| `docs/` | Production release notes, historical proposal, milestones, public media and project vision |
| `pool-r2/` | Public Miningcore compatibility patch, coin definition, safe example configuration and setup instructions |
| `src/` | Selected, historical consensus and genesis source snapshot; not a complete buildable r2 node tree |
| `tools/` | Published monetary-policy audit tooling for the source snapshot |
| [PUBLICATION_SCOPE.md](PUBLICATION_SCOPE.md) | Public/private source boundary |
| [SECURITY.md](SECURITY.md) | Security guidance and reporting |
| [UPSTREAM.md](UPSTREAM.md), [LICENSE](LICENSE) | Upstream attribution and licensing |

GitHub Releases retains historical package names and test releases for traceability. The r2 operator release currently carries a legacy candidate label; the matching Linux node has been deployed to the official mainnet. Use the current-release table above rather than treating release ordering or old filenames as a version recommendation.

## Lajkto Fox 🦊

**What does the fox say? LAJKTO!**

Meet **Lajkto Fox**, the official LKCT community mascot. The fox represents the playful side of the project alongside its technical documentation and independent RandomX CPU mining network.

![Lajkto Fox, official LKCT community mascot](https://lajkto.eu/lkct/assets/lajkto-fox-blue.png)

[Meet Lajkto Fox on the official website](https://lajkto.eu/lkct/#lajkto-fox)

*The mascot is community artwork, not a promise of market value, returns or exchange listing.*

## Publication boundary

This is **not a dump of the entire internal development tree**.

Experimental and service-layer work such as storage architecture, advertising/content systems, internal deployment infrastructure, private operational runbooks, unpublished roadmap material, credentials, backend configuration and other non-consensus research are intentionally excluded.

That boundary is deliberate: consensus behavior should be inspectable, while unrelated unpublished product research does not need to be exposed merely to demonstrate blockchain transparency.

See [PUBLICATION_SCOPE.md](PUBLICATION_SCOPE.md).

## Upstream

LKCT contains substantial software originating from the Monero Project, CryptoNote developers and other upstream projects.

The published upstream-derived files retain their original copyright notices and licensing terms. See [LICENSE](LICENSE) and the headers of individual source files.

This repository does not claim ownership of upstream Monero/CryptoNote work.

## Security

Do not place wallet seeds, private spend/view keys, exchange credentials, RPC passwords, server secrets or other private material in issues or pull requests.

See [SECURITY.md](SECURITY.md).

## Status

LKCT is an actively developed project. Publication of a source file here means that file has been selected for public technical inspection. It does not mean every experimental LKCT component has been published or that unpublished components are covered by the same license.
