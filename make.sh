#!/bin/bash
echo project-agv compileren..
read -p "op welke poort zit je arduino aangesloten? bijvoorbeeld: COM1, COM2.. (niks voor COM3):" poort
poort=${poort:-COM3} 
echo poort ${poort} word er gebruikt..
make PORT=${poort}
echo klaar, druk op een toets om dit venster te sluiten..
read -rsn1