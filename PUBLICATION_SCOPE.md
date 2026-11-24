# LKCT Public Source Publication Scope

This repository is a **reviewed public transparency snapshot**, not the complete internal LKCT development workspace.

## Included

Public material includes selected code and documentation for inspecting LKCT's blockchain identity and monetary policy, signed public distribution links, and a credential-free operator starter kit. The selected consensus source is a historical snapshot, not the complete r2 source tree.

At the time of this snapshot, that includes:

- LKCT network / monetary constants
- emission and block-reward logic
- genesis monetary-policy self-test
- monetary-policy audit tooling
- required upstream copyright and license notices
- production release notes and public installation guides
- selected Miningcore compatibility changes and sanitized example configuration in `pool-r2/`

## Intentionally excluded

The following categories are not part of this public snapshot:

- Lajkto Storage implementation and architecture
- advertising, content-market and moderation systems
- unreleased wallet product experiments
- internal roadmap and master-plan documents
- private deployment and production runbooks
- private pool backend internals and actual production configuration
- private APIs and infrastructure configuration
- credentials, keys, tokens and RPC secrets
- unreleased commercial or experimental service-layer code

Exclusion does not imply that a component is secret forever. It means publication is handled separately after technical, security and licensing review.

## Licensing boundary

Files derived from Monero, CryptoNote or other third-party projects remain subject to their respective licenses and copyright notices.

No statement in this document removes permissions already granted by an upstream license.

Conversely, this repository grants no rights to LKCT material that is **not actually published here**.
