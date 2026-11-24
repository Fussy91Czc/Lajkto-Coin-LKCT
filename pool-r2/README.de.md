# Eigener LKCT-Mining-Pool – PPLNS und SOLO

**LKCT v1.2 r2, Protokoll v17 ab Block 100.000.** Dieses Starterpaket richtet sich an unabhängige Poolbetreiber.

Vollständige Befehle: [README.md](README.md). Die [Beispielkonfiguration](miningcore.example.json) enthält PPLNS (4450), SOLO (4451) und mobiles PPLNS (4452). Die [Coin-Definition](lkct-coins.json) enthält RandomX, acht Dezimalstellen und die LKCT-Adresspräfixe. Der Patch ist an die dokumentierte Miningcore-Revision gebunden.

1. Signierten r2-Node [herunterladen](https://lajkto.eu/lkct/download.html#operator-node), Signatur prüfen und synchronisieren. Bei einem Upgrade die vorhandene Blockchain erhalten.
2. Separate Pool-Wallet erstellen, Seed offline sichern und Wallet-RPC nur auf 127.0.0.1:31790 betreiben. Node-RPC 31781 bleibt ebenfalls privat. Das geprüfte Beispiel verwendet Wallet-RPC ohne Login ausschließlich auf Loopback eines isolierten, vertrauenswürdigen Hosts. Auf gemeinsam genutzten Hosts ist zusätzliche geprüfte Zugriffssicherung nötig.
3. Miningcore nach dem Befehlsleitfaden bauen, Patch anwenden und eine eigene PostgreSQL-Datenbank anlegen. Die Platzhalter in einer privaten Konfigurationskopie ersetzen. Alle Beispiel-Stratum-Ports sind zunächst nur lokal erreichbar.
4. Miningcore starten und Jobs sowie akzeptierte Shares prüfen. Automatische Auszahlungen sind absichtlich deaktiviert.
5. Blöcke, Bestätigungen, Reorganisationen, Auszahlungen und Wiederherstellung isoliert testen, bevor der Pool öffentlich geöffnet oder Auszahlungen aktiviert werden. Die alte Miningcore-Basis verwendet .NET 6 ohne regulären Support; vor öffentlichem Betrieb eine unterstützte Laufzeit und Sicherheitsupdates prüfen.

```sh
# PPLNS
xmrig -a rx/0 -o 127.0.0.1:4450 -u DEINE_LKCT_ADRESSE.worker1 -p x
# SOLO
xmrig -a rx/0 -o 127.0.0.1:4451 -u DEINE_LKCT_ADRESSE.worker1 -p x
# Mobiles PPLNS
xmrig -a rx/0 -o 127.0.0.1:4452 -u DEINE_LKCT_ADRESSE.mobile -p x
```

Einen Modus auswählen. Für den offiziellen Pool 127.0.0.1 durch lajkto.eu ersetzen. Für den eigenen öffentlichen Pool den eigenen Hostnamen und passende Stratum-Bindings verwenden.

**Prüfumfang:** LAJKTO betreibt PPLNS und SOLO bereits mit r2. Isolierte Stratum-Tests aller drei Ports sowie 26 akzeptierte Shares waren erfolgreich. Ein neuer, unabhängiger Build dieses veröffentlichten Starterpakets und Auszahlungen nach dem Hard Fork wurden noch nicht getestet. Kein unbeaufsichtigter Produktionsinstaller.
