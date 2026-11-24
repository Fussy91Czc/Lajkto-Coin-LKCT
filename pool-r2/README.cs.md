# Vlastní LKCT pool – PPLNS a SOLO

**LKCT v1.2 r2, aktivace protokolu v17 na bloku 100 000.** Balíček je určen provozovatelům vlastních poolů, nikoliv pouze těžařům.

Podrobný příkazový návod: [README.md](README.md). Konfigurace [miningcore.example.json](miningcore.example.json) obsahuje PPLNS (4450), SOLO (4451) a mobilní PPLNS (4452). [lkct-coins.json](lkct-coins.json) definuje RandomX, přesnost 8 desetinných míst a adresní prefixy LKCT. Přiložená oprava je určená přesně pro uvedenou revizi Miningcore.

1. Stáhni a ověř podepsaný uzel r2 z [oficiálního webu](https://lajkto.eu/lkct/download.html#operator-node). Spusť jej a vyčkej na synchronizaci. Při aktualizaci zachovej původní blockchain.
2. Založ vlastní samostatnou poolovou peněženku, bezpečně zálohuj seed a spusť wallet RPC na 127.0.0.1:31790. RPC uzlu 31781 a wallet RPC nesmí být veřejné. Ověřená ukázka používá wallet RPC bez přihlášení výhradně na loopbacku na izolovaném důvěryhodném serveru. Na sdíleném serveru je nutné další ověřené zabezpečení přístupu.
3. Připrav Miningcore podle příkazového návodu, aplikuj patch, založ vlastní PostgreSQL databázi. Doplň vlastní veřejnou adresu a lokální hesla do soukromé kopie konfigurace. Všechny služby v ukázce jsou zpočátku dostupné pouze lokálně.
4. Spusť Miningcore. Ověř přidělování úloh a přijaté shares. Automatické výplaty jsou záměrně vypnuté.
5. Před veřejným spuštěním proveď test skutečných bloků a výplat v izolovaném prostředí, včetně obnovy po chybě, a teprve poté povol výplaty. Starý základ Miningcore používá nepodporovaný .NET 6; před veřejným provozem řeš bezpečnostní aktualizace a podporovaný runtime.

```sh
# PPLNS
xmrig -a rx/0 -o 127.0.0.1:4450 -u TVOJE_LKCT_ADRESA.worker1 -p x
# SOLO
xmrig -a rx/0 -o 127.0.0.1:4451 -u TVOJE_LKCT_ADRESA.worker1 -p x
# Mobilní PPLNS
xmrig -a rx/0 -o 127.0.0.1:4452 -u TVOJE_LKCT_ADRESA.mobile -p x
```

Vyber jeden režim. Pro těžbu na našem poolu nahraď 127.0.0.1 za lajkto.eu. Pro vlastní veřejný pool použij vlastní doménu a správně nastav Stratum rozhraní a firewall.

**Rozsah ověření:** produkční LAJKTO pool používá PPLNS i SOLO na novém uzlu r2. Izolovaný test všech tří portů a 26 přijatých shares prošel. Samostatná čistá instalace tohoto zveřejněného balíčku na novém serveru ani produkční výplata po hard forku zatím nebyla ověřena. Nejde o bezobslužný instalátor ani kopii soukromé infrastruktury.
