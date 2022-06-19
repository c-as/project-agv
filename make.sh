#!/bin/bash
echo ---------------------------------------------------------------------------
echo make.sh: Project-agv compileren...
echo ---------------------------------------------------------------------------
read -p "make.sh: >> op welke poort zit je arduino aangesloten? bijvoorbeeld: COM1, COM2.. (niks voor COM3):" poort
poort=${poort:-COM3} 
echo ---------------------------------------------------------------------------
echo make.sh: Poort ${poort} word er gebruikt...
echo ---------------------------------------------------------------------------
echo make.sh: Make starten...
echo ---------------------------------------------------------------------------
make PORT=${poort}
echo ---------------------------------------------------------------------------
echo make.sh: Klaar, druk op een toets om dit venster te sluiten...
echo ---------------------------------------------------------------------------
read -rsn1