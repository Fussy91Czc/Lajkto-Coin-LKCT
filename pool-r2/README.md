# LKCT v1.2 r2 – PPLNS / SOLO pool setup

Release: 24 November 2026. Node version `0.18.5.1-a8f39fef5`. Protocol v17 activates at block **100000**. Install before that height; do not create a new chain or delete existing wallets/databases.

This starter kit contains a standalone coin definition, a credential-free Miningcore configuration, selected LKCT compatibility patches against Miningcore commit `171a262a3f7861bbb54178d385806b9afebcb0af`, and build instructions. The public configuration starts on loopback with automated payouts disabled. It is not a ready-to-run copy of the production LAJKTO pool or a guarantee of payout safety. The existing Miningcore base uses .NET 6, which is out of support; review dependencies and migrate to a supported runtime before public production use.

## 1. Install the signed r2 node

Download the [Linux x64 signed operator ZIP](https://lajkto.eu/lkct/downloads/LKCT-v1.2-RC-a8f39fef5-Linux-x86_64-r2-signed.zip). Windows operators can obtain the [Windows operator ZIP](https://lajkto.eu/lkct/downloads/LKCT-v1.2-RC-a8f39fef5-Windows-x64-r2-signed.zip); these pool backend instructions target Linux x86_64. Verify the signing key against your already trusted LKCT key, not merely a key downloaded alongside the package.

Linux outer ZIP SHA-256: `eeb3eb28cebfc2230b31bd095edfd557e5bfe04b54e5726f0e47c43f70d01a93`.

After extracting the outer ZIP in a clean directory, verify its inner archive:
```sh
openssl pkeyutl -verify -pubin -inkey /path/to/trusted-release-public.pem -rawin -in SHA256SUMS -sigfile SHA256SUMS.sig
sha256sum -c SHA256SUMS
mkdir node-r2
tar -xzf LKCT-v1.2-RC-a8f39fef5-Linux-x86_64-r2.tar.gz -C node-r2
node-r2/bin/lajktod --lkct-release-info
```
The Linux daemon SHA-256 must be `3dcd90f392c1e518957a3ebd61e2c60db1f6c3116bdacb98255a18225bc06c37`. The probe must report mainnet_ready=true, version 0.18.5.1-a8f39fef5, activation_height=100000, and the original mainnet genesis. A probe is not a substitute for validating the signature.

Run as a dedicated non-root user. For a **new** node:
```sh
mkdir -p "$HOME/.lkct-pool/chain"
node-r2/bin/lajktod --data-dir "$HOME/.lkct-pool/chain" --p2p-bind-ip 0.0.0.0 --p2p-bind-port 31780 --rpc-bind-ip 127.0.0.1 --rpc-bind-port 31781 --zmq-rpc-bind-ip 127.0.0.1 --zmq-rpc-bind-port 31782 --add-priority-node lajkto.eu:31780 --no-igd --check-updates disabled --non-interactive
```
For an existing node: back up its data and executable, stop it cleanly, and use its original data directory and configuration. Never open one LMDB with two daemons. Verify synchronization before continuing:
```sh
curl -fsS http://127.0.0.1:31781/get_info
curl -fsS http://127.0.0.1:31781/json_rpc -H 'Content-Type: application/json' -d '{"jsonrpc":"2.0","id":"1","method":"hard_fork_info","params":{"version":17}}'
```

## 2. Dedicated pool wallet and wallet RPC

Create a dedicated pool wallet, not your personal wallet. Set a strong password locally and back up its seed offline. Note its public mainnet address; enter it in both pool configurations. Do not send the seed to the mining software or publish it.
```sh
umask 077
mkdir -p "$HOME/.lkct-pool/wallet"
node-r2/bin/lajkto-wallet-cli --generate-new-wallet "$HOME/.lkct-pool/wallet/pool" --daemon-address 127.0.0.1:31781
```
Exit the CLI before starting the wallet RPC. Create a mode-0600 wallet RPC configuration file and a separate mode-0600 password file containing the wallet password, locally. Use actual absolute paths. Example config keys:
```ini
wallet-file=/absolute/path/to/pool
password-file=/absolute/path/to/wallet-password-file
daemon-address=127.0.0.1:31781
trusted-daemon=1
rpc-bind-ip=127.0.0.1
rpc-bind-port=31790
disable-rpc-login=1
non-interactive=1
```
Start:
```sh
node-r2/bin/monero-wallet-rpc --config-file /absolute/path/to/wallet-rpc.conf
```
The pinned Miningcore RPC client uses Basic authentication; this example follows the tested dedicated-host deployment with wallet RPC bound to loopback and RPC login disabled. Use only on an isolated, trusted host with no untrusted local users or services. Never expose either RPC port, including via a reverse proxy. For shared hosts use a reviewed authentication-compatible RPC gateway and access isolation instead. Wait for wallet synchronization. The example shares one dedicated payout wallet across two pool IDs managed by a single Miningcore process, as in our tested deployment; use separate wallets and RPCs if isolating funds.

## 3. Miningcore and PostgreSQL

Use an isolated Linux x64 build machine. Install PostgreSQL and the build prerequisites for the selected Miningcore revision (C/C++ compiler, CMake, git, make, Boost, OpenSSL, libsodium, ZeroMQ and the required .NET SDK). Pin the upstream source:
```sh
git clone https://github.com/oliverw/miningcore.git
cd miningcore
git checkout --detach 171a262a3f7861bbb54178d385806b9afebcb0af
git apply --check /absolute/path/to/kit/miningcore-lkct.patch
git apply /absolute/path/to/kit/miningcore-lkct.patch
cp /absolute/path/to/kit/build-libs-lkct.sh src/Miningcore/build-libs-linux.sh
chmod +x src/Miningcore/build-libs-linux.sh
dotnet publish src/Miningcore/Miningcore.csproj -c Release --framework net6.0 -o "$PWD/build-lkct"
```
The source kit contains the LKCT low-difficulty target correction, native compilation include fix and selected wallet payout compatibility changes. The native build helper builds CryptoNote, CryptoNight and RandomX v1.1.10 locally for the build CPU. Do not use this build for other algorithms or assume CPU-specific libraries are portable. This public source kit has not yet been independently rebuilt on a fresh host.

Create a separate database and role; set the password interactively rather than in shell history:
```sh
sudo -u postgres createuser --pwprompt lkctpool
sudo -u postgres createdb -O lkctpool lkctpool
psql -h 127.0.0.1 -U lkctpool -d lkctpool -f src/Miningcore/Persistence/Postgres/Scripts/createdb.sql
```
Run the schema only on a new database. Existing installations need a backup and schema review first. Do not expose PostgreSQL publicly.

Copy the kit's `lkct-coins.json` and `miningcore.example.json` into a private working directory, and make a private `miningcore.json` from the template. Replace **all** REPLACE_ placeholders with your own public pool address and PostgreSQL password. Set coinTemplates to the actual path of lkct-coins.json. The template has no fee recipients; set your own transparent fee policy if needed. Keep separate pool IDs and payout schemes. Keep the minimum payout and peer checks appropriate to your deployment; the example uses 20 LKCT and 3 peers.

Run from the directory containing the config and coin definition:
```sh
chmod 600 miningcore.json
dotnet /absolute/path/to/miningcore/build-lkct/Miningcore.dll -c miningcore.json
```
The template initially binds the API and all three Stratum ports to localhost. It has automatic payments disabled at both global and pool level. Check log output, node height and jobs before exposing any port.

## 4. Mine on your own pool

Use XMRig RandomX (rx/0). Replace YOUR_LKCT_ADDRESS with a valid receiving address. With the initial loopback config, run the miner on the pool host:
```sh
xmrig -a rx/0 -o 127.0.0.1:4450 -u YOUR_LKCT_ADDRESS.worker1 -p x
xmrig -a rx/0 -o 127.0.0.1:4451 -u YOUR_LKCT_ADDRESS.worker1 -p x
xmrig -a rx/0 -o 127.0.0.1:4452 -u YOUR_LKCT_ADDRESS.mobile -p x
```
Choose one command, not all three for the same worker. PPLNS 4450 shares rewards according to the PPLNS window. SOLO 4451 credits the finder of a confirmed block (subject to any configured fee); Miningcore records and pays balances, rather than paying directly in coinbase to the individual miner. Mobile PPLNS 4452 uses fixed difficulty 100. A share is not a found block.

The official LAJKTO pool uses the same three ports at `lajkto.eu`. When operating your own public pool, replace loopback Stratum bind addresses with the intended interface and use your own hostname in the miner command. Open only the intended Stratum TCP ports and, if desired, node P2P 31780. Do not publish wallet RPC, daemon RPC, PostgreSQL or administrative API.

## 5. Before real payouts or public launch

- Verify signed r2 node, canonical chain tip, peer connectivity and wallet synchronization.
- Test PPLNS and SOLO with an isolated database and wallet, accepted shares, block acceptance, maturity, reorg/orphan handling, and exactly-once payout accounting, including large fragmented payouts and interruption/recovery. Use an isolated test network for deliberately generated blocks. Never force artificial production difficulty.
- Confirm backups and recovery, correct operator payout address, fee policy, access controls, sufficient peer connectivity and accounting reconciliation.
- Only then deliberately enable paymentProcessing.enabled globally and for the intended pools, after stopping the test instance and reviewing the private configuration. Never run two payment processors against the same wallet/database.
- Monitor block and payment status, and retain the established consensus activation height 100000.

## Evidence and limitations

LAJKTO PPLNS and SOLO are already operating on mainnet r2. In isolated testing on 22 November 2026 the exact r2 node returned jobs on all three Stratum test ports; one-thread XMRig received 26 accepted shares and zero rejected. Those tests used the existing LAJKTO Miningcore build, not a new build of this public kit, and did not test live post-fork payouts. This kit is a deployment starting point; it does not expose the internal production configuration, wallet or credentials.

Node releases: https://lajkto.eu/lkct/download.html#operator-node
Public pool: https://lajkto.eu/pool/lkct.php
