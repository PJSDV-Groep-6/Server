# COMPILE INSTRUCTIES

<b> Requirements </b>
- Linux
- CMake
- build-essential (of de gekozen repo equivalent. base-devel op arch)

<b> Steps </b>
- cd naar de repo folder
- ``` /usr/bin/cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" . ```
- ```cmake --build . ```

Let op de punten aan het einde van de twee cmake commands.
De server executable heet "Server" en kan gestart worden met de command "./Server"


# Usage

De statefile (states.txt) wordt automatisch gemaakt op basis van welke meubel objecten aangemaakt worden.

De statefile kan handmatig worden bewerkt met ```nano states.txt``` of elke andere willekeurige tekst editor.

Om de statefile te monitoren kan de command ``` watch -n 0.5 cat states.txt``` gebruikt worden.

Om de Logfile te monitoren kan de command ```watch -n 0.5 tac log.txt``` gebruikt worden.
