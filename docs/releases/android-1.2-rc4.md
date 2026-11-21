# LKCT Wallet for Android 1.2-rc4

Public test release for Android ARM64, version code 17, package `eu.lajkto.lkctwallet`. Choose the APK for the signing certificate of your installed wallet and open it on your phone. Android will ask you to confirm the update. Keep the original installation and its data.

| Originally installed wallet | APK |
| --- | --- |
| R7, R8 or R8a | [LKCT-Wallet-v1.2-rc4-Android-arm64-from-R7-R8-R8a.apk](https://lajkto.eu/lkct/downloads/LKCT-Wallet-v1.2-rc4-Android-arm64-from-R7-R8-R8a.apk) |
| 22 September 2026 (Beta1/Beta2) | [LKCT-Wallet-v1.2-rc4-Android-arm64-from-20260922.apk](https://lajkto.eu/lkct/downloads/LKCT-Wallet-v1.2-rc4-Android-arm64-from-20260922.apk) |

The packages were built from LKCT wallet revision `f4c144199c89d79c0aeec7460bb2762c9bd94383`. The first update from R12 uses the matching APK. RC4 checks for future recommended releases on launch, on return to the foreground and every 15 minutes during use. A manual check is available under **Settings → Wallet updates → Check now**. The wallet verifies the downloaded file, package, version and original Android signing certificate before offering installation. R12 is the current recommended release.

Both R12 signing variants were upgraded in place on an Android 15 emulator. The encrypted test wallet, keys, address and private settings were preserved. The existing test wallet reopened in the updated app. An Android 11 test exercised the update offer, actual download and system confirmation. The ARM64 translator on that emulator could not run the complete wallet UI. Testing did not include a physical phone.

[LKCT download page](https://lajkto.eu/lkct/download.html#android-rc4) · [SHA-256 checksums](https://lajkto.eu/lkct/downloads/LKCT-Wallet-v1.2-rc4-Android-SHA256SUMS.txt)
