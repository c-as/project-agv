#!/bin/bash
echo project-agv compileren..
read -p "op welke poort zit je arduino aangesloten? (COM2, COM3, ..):" poort
poort=${poort:-COM3} 
echo poort ${poort} word er gebruikt..
make PORT=${poort}
echo klaar, druk op een toets om dit venster te sluiten..
read -rsn1