# Lajkto Coin Technology (LKCT)

Official public transparency repository for **Lajkto Coin Technology (LKCT)**.

LKCT is a CryptoNote-derived digital currency using RandomX proof of work. This repository publishes a deliberately reviewed subset of the LKCT consensus implementation so that network identity and monetary-policy changes can be inspected without publishing unrelated experimental or commercial service-layer work.

## Public project links

- Project and wallet downloads: https://lajkto.eu/lkct
- Mining pool: https://lajkto.eu/pool
- Main website: https://lajkto.eu

Wallet builds are available for Windows, Linux and Android from the official project site.

## What is published here

The current public snapshot includes the source that defines and verifies the core LKCT monetary-policy changes:

- maximum supply and atomic-unit configuration
- founder genesis allocation
- mining allocation
- block reward / halving logic
- one-minute target configuration
- LKCT fee-floor constants
- genesis monetary-policy self-test
- an independent monetary-policy audit script

The files under `src/` are real source files from the LKCT codebase, not rewritten pseudocode.

## Monetary policy

The current LKCT consensus constants represented by this snapshot are:

- maximum supply: **100,000,000 LKCT**
- genesis founder allocation: **15,000,000 LKCT**
- mining allocation: **85,000,000 LKCT**
- initial mining reward: **20 LKCT**
- target block interval: **60 seconds**
- decimal precision: **8 decimals**
- no tail emission

The source files in this repository are the authoritative basis for the implementation details of this published snapshot.

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
