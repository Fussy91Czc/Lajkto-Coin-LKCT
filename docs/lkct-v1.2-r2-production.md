# LKCT v1.2 r2 — production node release

**24 November 2026.** The official LAJKTO mainnet node has been upgraded to `0.18.5.1-a8f39fef5` (r2). The node is synchronized and the LAJKTO PPLNS and SOLO mining endpoints remain available.

**Activation remains fixed at block 100,000 (protocol v17).** Installing or hosting this node now does not activate staking early. Historic blocks remain governed by the original rules. All operators must upgrade before activation to avoid following incompatible rules. No third-party approval is required for the official release; other operators' upgrade status is not guaranteed.

## Downloads

- [Signed operator release on GitHub](https://github.com/Fussy91Czc/Lajkto-Coin-LKCT/releases/tag/v1.2-operator-r2)
- [Windows and Linux signed archives, node instructions and wallet downloads](https://lajkto.eu/lkct/download.html#operator-node)
- [Operator verification instructions](https://lajkto.eu/lkct/developers.html#operator-v12-r2)

The previously uploaded r2 archives are the published operator builds. Do not interpret the historical RC names as a different blockchain version.

| Signed operator archive | SHA-256 |
|---|---|
| LKCT-v1.2-RC-a8f39fef5-Linux-x86_64-r2-signed.zip | `eeb3eb28cebfc2230b31bd095edfd557e5bfe04b54e5726f0e47c43f70d01a93` |
| LKCT-v1.2-RC-a8f39fef5-Windows-x64-r2-signed.zip | `58eb6b8ae0a7c02276297449d3d2226730c95e5359e7255b7f1aeced78ac86e6` |

Verify the detached signature over SHA256SUMS with your trusted existing LKCT release public key, then verify the inner archive. The Linux archive's daemon matches the deployed production executable byte for byte: SHA-256 `3dcd90f392c1e518957a3ebd61e2c60db1f6c3116bdacb98255a18225bc06c37`. The Windows operator archive and wallet-managed Windows executable are separate builds/packaging; do not compare their binary hashes to the Linux executable.

## Wallet-managed node installation

In a compatible LKCT Wallet, open **Settings → Network & node → Download and install node v1.2**. The wallet validates the signed platform-specific manifest, downloads the selected payload, checks its SHA-256 and size, and selects the verified installation. On Android, confirm the system installation dialog. Enable node hosting after installation. Do not start another daemon on the same ports.

The signed revision-12002 feeds are available for [Windows x64](https://lajkto.eu/lkct/downloads/nodes/windows-x64.json), [Linux x64](https://lajkto.eu/lkct/downloads/nodes/linux-x64.json), [Debian 11 legacy x64](https://lajkto.eu/lkct/downloads/nodes/linux-legacy-x64.json) and [Android ARM64](https://lajkto.eu/lkct/downloads/nodes/android-arm64.json). All four manifest signatures and published payload hashes were checked on 24 November 2026. The Linux production binary and wallet-managed Windows binary reported the expected release version and activation height. Android physical-device hosting remains unverified.

## Release evidence and limits

Internal engineering review completed: dynamic PoW and isolated mainnet-parameter replay at blocks 99,999–100,001, 220,228 monetary-policy checks, 100,000 legacy subsidy comparisons, LMDB and staking maturity/withdrawal/reorganization tests. This is internal test evidence, not independent certification or a guarantee of financial returns. The 200-million LKCT staking reward reserve limits new reward commitments. The 0.75-LKCT security subsidy begins only after the original mining allocation is exhausted.

Back up node data and wallet recovery information securely before upgrading. Preserve the existing chain data; do not delete it or expose private RPC, wallet keys or passwords. P2P TCP 31780 remains public; unrestricted RPC 31781 should stay local. Activation is determined by blockchain height, not by the website or wallet download button.
