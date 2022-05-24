#!/bin/bash
echo building project-agv..
read -p "op welke poort zit je arduino aangesloten? (COM2, COM3, ..):" poort
poort=${poort:-COM3} 
echo poort ${poort} word er gebruikt..
make PORT=${poort}
echo done, waiting for keypress..
read -rsn1